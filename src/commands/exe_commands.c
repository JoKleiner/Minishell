/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:13:05 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/02 15:24:50 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	sig_bs_exe(int sig)
// {
// 	g_sig = sig;
// 	write(1, "Quit: 3\n", 8);
// }

// static void	sig_c_exe(int sig)
// {
// 	g_sig = sig;
// 	write(STDOUT_FILENO, "\n", 1);
// }

// static void	setup_execution_signals(void)
// {
// 	struct sigaction	act_bs;
// 	struct sigaction	act_c;

// 	ft_memset(&act_bs, 0, sizeof(act_bs));
// 	act_bs.sa_handler = sig_bs_exe;
// 	act_bs.sa_flags = 0;
// 	sigemptyset(&act_bs.sa_mask);
// 	sigaction(SIGQUIT, &act_bs, NULL);
// 	ft_memset(&act_c, 0, sizeof(act_c));
// 	act_c.sa_handler = sig_c_exe;
// 	act_c.sa_flags = 0;
// 	sigemptyset(&act_c.sa_mask);
// 	sigaction(SIGINT, &act_c, NULL);
// }

int	ft_execute_cmd_fork(char *path, t_token *stream, char ***copy_env)
{
	int	pid;
	int	status;
	int	exe_num;

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
