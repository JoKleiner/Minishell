/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:13:05 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/19 17:11:54 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_cmd_helper(char **try_paths, t_list *stream)
{
	char	*path;
	int		i;

	i = 0;
	if (access(TOKEN->arg[0], 0) == 0)
	{
		path = ft_strdup(TOKEN->arg[0]);
		if (!path)
			return (NULL);
		return (path);
	}
	while (try_paths[i])
	{
		path = ft_strjoin_delimit(try_paths[i], '/', TOKEN->arg[0]);
		if (!(path))
			return (NULL);
		if (access(path, 0) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	return (path);
}

// Checks if the command is in the evnp PATH.
static char	*ft_cmd_exists(t_list *stream, char **copy_env)
{
	char	*path;
	char	**try_paths;
	int		env_pos;

	if (ft_env_exists("PATH", copy_env) == false)
		return (NULL);
	env_pos = find_envp("PATH", copy_env);
	try_paths = ft_split(&(copy_env[env_pos])[5], ':');
	if (!try_paths)
		return (NULL);
	path = ft_cmd_helper(try_paths, stream);
	free_strarr(try_paths);
	return (path);
}

static void	ft_execute_cmd_fork(char *path, t_list *stream, char ***copy_env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (TOKEN->fd_out != STDOUT_FILENO)
			dup2(TOKEN->fd_out, STDOUT_FILENO);
		execve(path, TOKEN->arg, *copy_env);
	}
	waitpid(pid, 0, 0);
}

void	ft_execute_command(t_list *stream, char ***copy_env)
{
	char	*path;

	if (!TOKEN || !TOKEN->arg)
		return ;
	path = ft_strdup(TOKEN->arg[0]);
	if (!path)
		return (ft_error_cmd("Malloc failed.", "Error"));
	path = ft_str_tolower(path);
	if (ft_builtin_cmd(path, stream, copy_env) == true)
	{
		if (TOKEN->fd_out != 1)
			close(TOKEN->fd_out);
		return (free(path));
	}
	else
	{
		free(path);
		path = ft_cmd_exists(stream, *copy_env);
		if (!path)
			ft_error_cmd("Command not found", TOKEN->arg[0]);
		else
			ft_execute_cmd_fork(path, stream, copy_env);
	}
	if (TOKEN->fd_out != 1)
		close(TOKEN->fd_out);
}
