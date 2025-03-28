/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:13:05 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 14:08:21 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execute_cmd_fork(char *path, t_token *stream, char ***copy_env)
{
	int	pid;
	int	status;
	int	exe_num;

	pid = fork();
	if (pid == -1)
	{
		stream->error = errno;
		return (ft_errmal("execution fork:"), 1);
	}
	if (pid == 0)
	{
		if (stream->fd_out != STDOUT_FILENO)
			dup2(stream->fd_out, STDOUT_FILENO);
		exe_num = execve(path, stream->arg, *copy_env);
		exit(exe_num);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

void	ft_execute_command(t_token *stream, char ***copy_env)
{
	if (!stream->arg || !stream->arg[0])
		return ;
	if (stream->arg[0][0] == '\0')
		return (token_err(stream, 127), ft_error(CMD_NF, ""));
	if (ft_dot_syntax(stream->arg, stream, copy_env) == true)
		return ;
	if (ft_builtin_cmd(stream->arg[0], stream, copy_env) == true)
		return ;
	if (ft_cmd_in_path(stream, copy_env) == true)
		return ;
	if (ft_non_accessible(stream) == true)
		return ;
	if (ft_is_executable(stream->arg[0], stream, copy_env) == true)
		return ;
}
