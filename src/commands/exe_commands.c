/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:13:05 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/25 15:08:47 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execute_cmd_fork(char *path, t_list *stream, char ***copy_env)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		TOKEN->error = errno;
		return (ft_errmal("execution fork:"), 1);
	}
	if (pid == 0)
	{
		if (TOKEN->fd_out != STDOUT_FILENO)
			dup2(TOKEN->fd_out, STDOUT_FILENO);
		execve(path, TOKEN->arg, *copy_env);
		exit(errno);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

void	ft_execute_command(t_list *stream, char ***copy_env)
{
	if (!TOKEN->arg)
		return ;
	if (ft_dot_syntax(TOKEN->arg, stream, copy_env) == true)
		return ;
	if (ft_builtin_cmd(TOKEN->arg[0], stream, copy_env) == true)
		return ;
	if (ft_cmd_in_path(stream, copy_env) == true)
			return ;
	if (ft_non_accessible(stream) == true)
		return ;
	if (ft_is_executable(TOKEN->arg[0], stream, copy_env) == true)
		return ;
}
