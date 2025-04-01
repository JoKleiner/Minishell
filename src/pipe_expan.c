/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_expan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:51:14 by joklein           #+#    #+#             */
/*   Updated: 2025/04/01 15:21:29 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	end_mother_pipe(int *fds, int pid, t_token *stream, char **copy_env)
{
	int	status;

	close(fds[WR_IN]);
	if (waitpid(pid, &status, 0) == -1)
		status = 0;
	free_stream(stream);
	free_strarr(copy_env);
	exit(WEXITSTATUS(status));
}

void	mother_pipe(int i, char *input, t_token *stream, char ***copy_env)
{
	int	pipes;
	int	u;

	u = 0;
	pipes = 0;
	while (pipes < i)
	{
		if (input[u] == '|' && input[u - 1] != '>')
			pipes++;
		u++;
	}
	input = stream_input(input, u);
	stream_handle(input, copy_env, stream);
}

t_token	*setup_child(int *fds, char *input, t_token *stream, int num_pipes)
{
	int	ori_sdtin;

	ori_sdtin = stream->ori_sdtin;
	close(fds[WR_IN]);
	dup2(fds[RD_OUT], STDIN_FILENO);
	close(fds[RD_OUT]);
	free_stream(stream);
	stream = init_stream(NULL, ori_sdtin, num_pipes);
	if (stream == NULL)
	{
		free(input);
		ft_errmal("Malloc failed.");
		exit(ENOMEM);
	}
	return (stream);
}
