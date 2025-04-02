/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:25:38 by joklein           #+#    #+#             */
/*   Updated: 2025/04/02 15:24:54 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_input_heredoc(void)
{
	char	*line;
	char	*input;

	if (isatty(STDIN_FILENO))
		input = readline("> ");
	else
	{
		line = get_next_line(STDIN_FILENO);
		input = ft_strtrim(line, "\n");
		free(line);
	}
	return (input);
}

static int	append_in_file(char *input, char *here_doc)
{
	int	fd;

	fd = open(here_doc, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_errmal("open failed");
		return (1);
	}
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	close(fd);
	return (0);
}

static int	handle_heredoc_input(char *str, char *here_input, char *here_doc,
		char **copy_env)
{
	t_token	*stream;
	int		error_num;

	stream = init_stream(NULL, 0, 0);
	if (!stream)
		return (free(here_doc), free(str), ENOMEM);
	while (ft_strncmp(here_input, str, ft_strlen(str) + 1) != 0)
	{
		here_input = dollar_handle(here_input, copy_env, stream);
		error_num = stream->error;
		if (!here_input)
			return (free(here_doc), free(str), free_sm(stream), error_num);
		if (append_in_file(here_input, here_doc) != 0)
			return (free(here_doc), free(str), free(here_input),
				free_sm(stream), 1);
		free(here_input);
		here_input = get_input_heredoc();
		if (return_value(0, false))
			return (free_sm(stream), free(here_input), free(str),
				unlink(here_doc), free(here_doc), 130);
		if (!here_input)
			return (printf("warning: here-document delimited (wanted `%s')\n",
					str), free(here_doc), free(str), free_sm(stream), 0);
	}
	return (free_sm(stream), free(here_input), free(str), free(here_doc), 0);
}

void	sigint_heredoc_handler(int signo)
{
	(void)signo;
	return_value(1, true);
	printf("\n");
	close(STDIN_FILENO);
}

int	heredoc_child_process(char *str, char *here_doc, char **copy_env)
{
	char	*here_input;
	char	*line;

	return_value(0, true);
	signal(SIGINT, sigint_heredoc_handler);
	if (isatty(STDIN_FILENO))
		here_input = readline("> ");
	else
	{
		line = get_next_line(STDIN_FILENO);
		here_input = ft_strtrim(line, "\n");
		free(line);
	}
	if (return_value(0, false))
	{
		if (here_input)
			free(here_input);
		return (free(str), unlink(here_doc), free(here_doc), 130);
	}
	if (!here_input)
		return (printf("warning: here-document delimited (wanted `%s')\n", str),
			free(here_doc), free(str), 0);
	return (handle_heredoc_input(str, here_input, here_doc, copy_env));
}
