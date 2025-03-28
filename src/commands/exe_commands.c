/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:13:05 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 15:26:31 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sig_bs_handler(int sig)
{
	(void)sig;
	write(1, "Quit: 3\n", 8);
}

int	ft_execute_cmd_fork(char *path, t_token *stream, char ***copy_env)
{
	int					pid;
	int					status;
	int					exe_num;
	struct sigaction	act_bs;

	ft_memset(&act_bs, 0, sizeof(act_bs));
	act_bs.sa_handler = sig_bs_handler;
	act_bs.sa_flags = SA_SIGINFO;
	sigemptyset(&act_bs.sa_mask);
	sigaction(SIGQUIT, &act_bs, NULL);
	pid = fork();
	if (pid == -1)
		return (token_err(stream, errno), setup_signals(),
			ft_errmal("execution fork:"), 1);
	if (pid == 0)
	{
		if (stream->fd_out != STDOUT_FILENO)
			dup2(stream->fd_out, STDOUT_FILENO);
		exe_num = execve(path, stream->arg, *copy_env);
		exit(exe_num);
	}
	waitpid(pid, &status, 0);
	setup_signals();
	return (WEXITSTATUS(status));
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
