/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:13:05 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/10 11:41:17 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Checks if the command is a self-made command
static bool	ft_builtin_cmd(t_list *stream)
{
	if (ft_strncmp(TOKEN->arg[0], "echo", 4) == 0)
		return (ft_exe_echo(stream), true);
	else if (ft_strncmp(TOKEN->arg[0], "cd", 2) == 0)
		return (ft_exe_cd(stream), true);
	else if (ft_strncmp(TOKEN->arg[0], "pwd", 3) == 0)
		return (ft_exe_pwd(stream), true);
	else if (ft_strncmp(TOKEN->arg[0], "export", 7) == 0)
		return (ft_exe_export(stream), true);
	else if (ft_strncmp(TOKEN->arg[0], "unset", 5) == 0)
		return (ft_exe_unset(stream), true);
	else if (ft_strncmp(TOKEN->arg[0], "env", 3) == 0)
		return (ft_exe_env(stream), true);
	else if (ft_strncmp(TOKEN->arg[0], "exit", 4) == 0)
		return (ft_exe_exit(stream), true);
	return (false);
}

// Checks if the command is in the evnp PATH.
static char	*ft_cmd_exists(t_list *stream)
{
	int		i;
	char	*path;
	char	**try_paths;

	try_paths = ft_split(environ[4], ':');
	if (!try_paths)
		exit(1);
	i = 0;
	while (try_paths[i])
	{
		path = ft_strjoin(try_paths[i], TOKEN->arg[0]);
		if (!path)
			exit(1);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}	
	return (path);
}

// Executes self-made and builtin commands.
// Error if command does not exist.
void	ft_execute_command(t_list *stream)
{
	char	*path;
	int		pid;

	if (ft_builtin_cmd(stream) == true)
	{
		if (TOKEN->fd_out != 1)
			close(TOKEN->fd_out);
	}
	else
	{
		path = ft_cmd_exists(stream);
		if (path != NULL)
		{
			dup2(TOKEN->fd_out, 1);
			execve(path, TOKEN->arg, environ);
			free(path);
		}
		else
			ft_error_cmd("Command not found", TOKEN->arg[0]);
	}
	(void)pid;
}
