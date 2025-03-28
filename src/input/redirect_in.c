/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:41:23 by joklein           #+#    #+#             */
/*   Updated: 2025/03/28 14:08:21 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_fd_in(t_token *stream)
{
	int	fd;

	if (stream->fd_in == -3 || stream->fd_in == -4)
	{
		if (stream->fd_in == -3)
			fd = open(stream->in_file, O_RDONLY);
		if (stream->fd_in == -4)
			fd = open(stream->hd_file, O_RDONLY);
		if (fd == -1)
			return (ft_errmal("open failed"), 1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (ft_errmal("dup2 failed"), 1);
	}
	return (0);
}

static int	file_in(char *input, int i, t_token *stream)
{
	int		i_temp;
	char	*str;
	int		fd;

	i_temp = i;
	while (input[i] && !wh_space(input[i]) && !spec_char(input[i]))
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_until_char(i, input, input[i]);
		i++;
	}
	str = str_quote_less(&input[i_temp], i - i_temp);
	if (!str)
		return (mem_fail(stream), -1);
	if (stream->in_file)
		free(stream->in_file);
	stream->in_file = str;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_error(": No such file or directory", str),
			stream->error = 1, -1);
	close(fd);
	stream->fd_in = -3;
	return (i);
}

static int	set_heredoc(int i, char *input, t_token *stream)
{
	char	*here_doc;
	char	*num_str;

	num_str = ft_itoa(stream->stream_num);
	if (!num_str)
		return (ft_errmal("Malloc failed."), -1);
	here_doc = ft_strjoin(".heredoc", num_str);
	if (!here_doc)
		return (free(num_str), ft_errmal("Malloc failed."), -1);
	stream->hd_file = here_doc;
	stream->fd_in = -4;
	free(num_str);
	i = skip_heredoc(i, input);
	return (i);
}

int	redirect_in(char *input, int i, t_token *stream)
{
	i++;
	if (input[i] == '<')
	{
		i++;
		while (wh_space(input[i]))
			i++;
		i = set_heredoc(i, input, stream);
	}
	else
	{
		while (wh_space(input[i]))
			i++;
		i = file_in(input, i, stream);
	}
	if (i == -1)
		return (free(input), -1);
	if (input[i] == '\0')
		i--;
	return (i);
}
