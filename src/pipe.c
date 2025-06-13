/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:48:46 by joklein           #+#    #+#             */
/*   Updated: 2025/04/02 15:24:50 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	last_pipe(int i, char *input, t_token *stream, char ***copy_env)
{
	int	pipes;
	int	return_num;
	int	u;

	u = 0;
	pipes = 0;
	while (pipes < i)
	{
		if (input[u] == '\'' || input[u] == '\"')
			u = skip_until_char(u, input, input[u]);
		if (input[u] == '|' && input[u - 1] != '>')
			pipes++;
		u++;
	}
	input = stream_input(input, u);
	return_num = stream_handle(input, copy_env, stream);
	free_sm(stream);
	free_strarr(*copy_env);
	exit(return_num);
}

static int	pipe_fork(int *fds, char *input)
{
	int	pipe_error;
	int	pid;

	pipe_error = pipe(fds);
	pid = fork();
	if (pipe_error == -1 || pid == -1)
	{
		free(input);
		ft_errmal("fork failed.");
		exit(errno);
	}
	return (pid);
}

static void	execute_pipes(int num_pipe, char *input, char ***copy_env,
		t_token *stream)
{
	int	fds[2];
	int	i;
	int	pid;

	i = 0;
	pid = 0;
	while (i <= num_pipe)
	{
		if (pid == 0 && i != num_pipe)
		{
			pid = pipe_fork(fds, input);
			if (pid == 0)
				stream = setup_child(fds, input, stream, i + 1);
			else
			{
				close(fds[RD_OUT]);
				stream->fd_out = fds[WR_IN];
				mother_pipe(i, input, stream, copy_env);
				end_mother_pipe(fds, pid, stream, *copy_env);
			}
		}
		else
			last_pipe(i, input, stream, copy_env);
		i++;
	}
}

int	pipe_handle(int num_pipe, int ori_sdtin, char *input, char ***copy_env)
{
	t_token	*stream;
	int		pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_errmal("fork failed"), 1);
	if (pid == 0)
	{
		stream = init_stream(NULL, ori_sdtin, 0);
		if (stream == NULL)
		{
			free(input);
			ft_errmal("Malloc failed.");
			exit(ENOMEM);
		}
		stream->ori_sdtin = ori_sdtin;
		execute_pipes(num_pipe, input, copy_env, stream);
	}
	waitpid(pid, &status, 0);
	usleep(1000);
	return (WEXITSTATUS(status));
}
