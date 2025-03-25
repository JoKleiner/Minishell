/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:25:38 by joklein           #+#    #+#             */
/*   Updated: 2025/03/25 12:26:34 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	append_in_file(char *input, char *here_doc)
{
	int	fd;

	fd = open(here_doc, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_errmal("open failed");
		return (errno);
	}
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	close(fd);
	return (0);
}

static int	handle_heredoc_input(char *str, char *here_input, char *here_doc,
		char **copy_env)
{
	t_list	*stream;

	stream = init_stream(NULL, 0, 0);
	if (stream == NULL)
		return (free(str), ENOMEM);
	while (ft_strncmp(here_input, str, ft_strlen(str) + 1) != 0)
	{
		here_input = dollar_handle(here_input, copy_env, stream);
		if (!here_input)
			return (free(str), TOKEN->error);
		if (append_in_file(here_input, here_doc) != 0)
			return (free(str), free(here_input), errno);
		free(here_input);
		here_input = readline("> ");
		if (!here_input)
			return (free(str), errno);
	}
	free(here_input);
	free(str);
	return (errno);
}

void	heredoc_child_process(char *str, char *here_doc, char **copy_env)
{
	char	*here_input;

	signal(SIGINT, SIG_DFL);
	here_input = readline("> ");
	if (!here_input)
		exit(errno);
	exit(handle_heredoc_input(str, here_input, here_doc, copy_env));
}
