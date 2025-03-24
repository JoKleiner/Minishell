/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:51:46 by joklein           #+#    #+#             */
/*   Updated: 2025/03/24 12:57:50 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*hd_num_file(int i, t_list *stream)
{
	char	*here_doc;
	char	*num_str;

	num_str = ft_itoa(i);
	if (!num_str)
		return (mem_fail(stream), NULL);
	here_doc = ft_strjoin(".heredoc", num_str);
	free(num_str);
	if (!here_doc)
		return (mem_fail(stream), NULL);
	return (here_doc);
}

int	append_in_file(char *input, t_list *stream)
{
	int	fd;

	fd = open(TOKEN->hd_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		TOKEN->error = errno;
		ft_errmal("open failed");
		return (1);
	}
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	close(fd);
	return (0);
}

char	*create_hd_file(t_list *stream)
{
	char	*here_doc;
	int		i;
	int		fd;

	if (TOKEN->hd_file == NULL)
	{
		i = 1;
		here_doc = hd_num_file(i, stream);
		if (!here_doc)
			return (NULL);
		while (!access(here_doc, F_OK))
		{
			i++;
			free(here_doc);
			here_doc = hd_num_file(i, stream);
			if (!here_doc)
				return (NULL);
		}
	}
	else
		here_doc = TOKEN->hd_file;
	fd = open(here_doc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (TOKEN->error = errno, ft_errmal("open failed"), NULL);
	return (close(fd), here_doc);
}

char	*initialize_heredoc(t_list *stream)
{
	char	*here_doc;

	here_doc = create_hd_file(stream);
	if (!here_doc)
		return (NULL);
	TOKEN->fd_in = -1;
	while (TOKEN->fd_in == -1)
	{
		TOKEN->fd_in = open("heredoc.lock", O_CREAT | O_EXCL, 0644);
		usleep(100);
	}
	return (here_doc);
}

void	handle_heredoc_input(char *str, char *here_input, t_list *stream,
		char **copy_env)
{
	while (ft_strncmp(here_input, str, ft_strlen(str) + 1) != 0)
	{
		here_input = dollar_handle(here_input, copy_env, stream);
		if (!here_input)
		{
			close(TOKEN->fd_in);
			exit(TOKEN->error);
		}
		if (append_in_file(here_input, stream) != 0)
		{
			free(str);
			free(here_input);
			close(TOKEN->fd_in);
			exit(TOKEN->error);
		}
		free(here_input);
		here_input = readline("> ");
		if (!here_input)
			break ;
	}
	close(TOKEN->fd_in);
	exit(errno);
}

void	heredoc_child_process(char *str, char *here_doc, t_list *stream,
		char **copy_env)
{
	char	*here_input;

	signal(SIGINT, SIG_DFL);
	if (dup2(TOKEN->ori_sdtin, STDIN_FILENO) == -1)
	{
		ft_errmal("dup2 failed");
		exit(errno);
	}
	here_input = readline("> ");
	if (!here_input)
	{
		close(TOKEN->fd_in);
		exit(errno);
	}
	TOKEN->hd_file = here_doc;
	handle_heredoc_input(str, here_input, stream, copy_env);
}

int	create_heredoc(char *str, t_list *stream, char **copy_env)
{
	char	*here_doc;
	int		pid;
	int		status;

	here_doc = initialize_heredoc(stream);
	if (!here_doc)
		return (free(str), -1);
	pid = fork();
	if (pid == -1)
		return (ft_errmal("fork failed"), TOKEN->error = errno, -1);
	if (pid == 0)
		heredoc_child_process(str, here_doc, stream, copy_env);
	waitpid(pid, &status, 0);
	close(TOKEN->fd_in);
	unlink("heredoc.lock");
	if (status != 0)
		return (TOKEN->error = status, -1);
	TOKEN->hd_file = here_doc;
	TOKEN->fd_in = -4;
	free(str);
	return (0);
}

int	heredoc(int i, char *input, t_list *stream, char **copy_env)
{
	int		i_temp;
	char	*str;

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
	if (create_heredoc(str, stream, copy_env) == -1)
		return (-1);
	return (i);
}
