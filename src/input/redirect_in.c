/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:41:23 by joklein           #+#    #+#             */
/*   Updated: 2025/03/25 15:18:24 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	file_in(char *input, int i, t_list *stream)
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
	if (TOKEN->in_file)
		free(TOKEN->in_file);
	TOKEN->in_file = str;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (ft_error(": No such file or directory", str),
			TOKEN->error = errno, -1);
	close(fd);
	TOKEN->fd_in = -3;
	return (i);
}

static int	set_heredoc(int i, char *input, t_list *stream)
{
	char	*here_doc;
	char	*num_str;

	num_str = ft_itoa(TOKEN->stream_num);
	if (!num_str)
		return (ft_errmal("Malloc failed."), -1);
	here_doc = ft_strjoin(".heredoc", num_str);
	if (!here_doc)
		return (free(num_str), ft_errmal("Malloc failed."), -1);
	TOKEN->hd_file = here_doc;
	TOKEN->fd_in = -4;
	free(num_str);
	i = skip_heredoc(i, input);
	return (i);
}

int	redirect_in(char *input, int i, t_list *stream)
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
