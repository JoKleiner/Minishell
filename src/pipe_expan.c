/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_expan.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:51:14 by joklein           #+#    #+#             */
/*   Updated: 2025/03/25 12:54:49 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	end_mother_pipe(int *fds, int pid, t_list *stream, int return_num)
{
	int	status;

	close(fds[WR_IN]);
	waitpid(pid, &status, 0);
	free_stream(stream);
	if (WEXITSTATUS(status) != 0)
		exit(WEXITSTATUS(status));
	exit(return_num);
}

int	mother_pipe(int i, char *input, t_list *stream, char ***copy_env)
{
	int	pipes;
	int	u;
	int	return_num;

	u = 0;
	pipes = 0;
	while (pipes < i)
	{
		if (input[u] == '|')
			pipes++;
		u++;
	}
	input = stream_input(input, u);
	return_num = stream_handle(input, copy_env, stream);
	return (return_num);
}

t_list	*setup_child(int *fds, char *input, t_list *stream, int num_pipes)
{
	close(fds[WR_IN]);
	dup2(fds[RD_OUT], STDIN_FILENO);
	close(fds[RD_OUT]);
	stream = init_stream(NULL, TOKEN->ori_sdtin, num_pipes);
	if (stream == NULL)
	{
		free(input);
		ft_errmal("Malloc failed.");
		exit(ENOMEM);
	}
	return (stream);
}
