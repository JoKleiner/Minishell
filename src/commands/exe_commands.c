/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:13:05 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/21 17:19:26 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execute_cmd_fork(char *path, t_list *stream, char ***copy_env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		TOKEN->error = errno;
		return (ft_errmal("execution fork:"));
	}
	if (pid == 0)
	{
		if (TOKEN->fd_out != STDOUT_FILENO)
			dup2(TOKEN->fd_out, STDOUT_FILENO);
		execve(path, TOKEN->arg, *copy_env);
	}
	waitpid(pid, 0, 0);
}

static void	ft_execute_cmd_helper(char *path, t_list *stream, char ***copy_env)
{
	if (ft_builtin_cmd(path, stream, copy_env) == true)
		return (free(path));
	else
	{
		free(path);
		path = ft_cmd_exists(stream, *copy_env);
		if (!path)
		{
			TOKEN->error = 127;
			ft_error_cmd("Command not found", TOKEN->arg[0]);
		}
		else
		{
			ft_execute_cmd_fork(path, stream, copy_env);
		}
	}
}

void	ft_execute_command(t_list *stream, char ***copy_env)
{
	char	*path;

	if (!TOKEN || !TOKEN->arg)
	{
		TOKEN->error = 0;
		return ;
	}
	if (ft_dot_syntax(stream, copy_env) == false)
		return ;
	path = ft_strdup(TOKEN->arg[0]);
	if (!path)
	{
		TOKEN->error = 12;
		return (ft_error_cmd("Malloc failed.", "Error"));
	}
	path = ft_str_tolower(path);
	ft_execute_cmd_helper(path, stream, copy_env);
	if (TOKEN->fd_out != 1)
		close(TOKEN->fd_out);
}
