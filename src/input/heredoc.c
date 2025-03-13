/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:51:46 by joklein           #+#    #+#             */
/*   Updated: 2025/03/13 13:06:17 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_hd_file(t_list *stream)
{
	int		fd;
	char	*here_doc;
	int		i;

	if (TOKEN->hd_file == NULL)
	{
		i = 1;
		here_doc = ft_strjoin(".heredoc", ft_itoa(i));
		if (!here_doc)
			return (NULL);
		while (!access(here_doc, F_OK))
		{
			i++;
			free(here_doc);
			here_doc = ft_strjoin(".heredoc", ft_itoa(i));
			if (!here_doc)
				return (NULL);
		}
	}
	else
		here_doc = TOKEN->hd_file;
	fd = open(here_doc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (NULL);
	return (close(fd), here_doc);
}

int	append_in_file(char *input, char *str)
{
	int	fd;

	fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	close(fd);
	return (0);
}

int	create_heredoc(char *str, t_list *stream, char **copy_env)
{
	char	*here_input;
	char	*here_doc;

	here_doc = create_hd_file(stream);
	if (!here_doc)
		return (free(str), -1);
	here_input = readline("> ");
	if (!here_input)
		return (free(str), free(here_doc), -1);
	while (ft_strncmp(here_input, str, ft_strlen(str)) != 0)
	{
		here_input = dollar_handle(here_input, copy_env);
		if (append_in_file(here_input, here_doc) == -1)
			return (free(str), free(here_doc), free(here_input), -1);
		free(here_input);
		here_input = readline("> ");
		if (!here_input)
			return (free(str), free(here_doc), -1);
	}
	free(here_input);
	TOKEN->hd_file = here_doc;
	TOKEN->fd_in = 4;
	free(str);
	return (0);
}

int	heredoc(int i, char *input, t_list *stream, char **copy_env)
{
	int		i_temp;
	char	*str;

	i_temp = i;
	while (input[i] && !wh_space(input[i]) && !spec_char_wo_dol(input[i]))
	{
		if (input[i] == '\'')
			i = skip_until_char(i, input, '\'');
		if (input[i] == '\"')
			i = skip_until_char(i, input, '\"');
		i++;
	}
	str = str_quote_less(&input[i_temp], i - i_temp);
	if (!str)
		return (-1);
	if (str[0] == '\0')
		return (free(str), write(1, "syntax error\n", 13), -1);
	if (create_heredoc(str, stream, copy_env) == -1)
		return (-1);
	return (i);
}
