/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:13:05 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/02 16:57:38 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_execute_cmd_fork(char *path, t_token *stream, char ***copy_env)
{
	int	pid;
	int	status;
	int	exe_num;

	ft_handler_signals(stream->arg[0]);
	pid = fork();
	if (pid == -1)
		return (token_err(stream, errno), setup_signals(),
			ft_errmal("execution fork:"), 1);
	if (pid == 0)
	{
		sig_default(SIGINT);
		sig_default(SIGQUIT);
		if (stream->fd_out != STDOUT_FILENO)
			dup2(stream->fd_out, STDOUT_FILENO);
		exe_num = execve(path, stream->arg, *copy_env);
		free_sm(stream);
		free_strarr(*copy_env);
		ft_error("cannot execute binary file", "execve");
		exit(exe_num);
	}
	waitpid(pid, &status, 0);
	if (g_sig == SIGINT || g_sig == SIGQUIT)
		return (setup_signals(), g_sig + 128);
	return (setup_signals(), WEXITSTATUS(status));
}

void	ft_execute_command(t_token *stream, char ***copy_env)
{
	if (!stream->arg || !stream->arg[0])
		return ;
	if (stream->arg[0][0] == '\0')
		return (token_err(stream, 127), ft_error(CMD_NF, ""));
	if (ft_dot_syntax(stream->arg, stream, copy_env) == true)
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
