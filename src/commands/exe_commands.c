/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:13:05 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/18 16:09:34 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Checks if the command is a self-made command
static bool	ft_builtin_cmd(char *name, t_list *stream, char ***copy_env)
{
	if (ft_strncmp(name, "echo", 5) == 0)
		return (ft_exe_echo(stream), true);
	else if (ft_strncmp(name, "cd", 3) == 0)
		return (ft_exe_cd(stream, copy_env), true);
	else if (ft_strncmp(name, "pwd", 4) == 0)
		return (ft_exe_pwd(stream), true);
	else if (ft_strncmp(name, "export", 8) == 0)
		return (ft_exe_export(stream, copy_env), true);
	else if (ft_strncmp(name, "unset", 6) == 0)
		return (ft_exe_unset(stream, copy_env), true);
	else if (ft_strncmp(name, "env", 4) == 0)
		return (ft_exe_env(stream, *copy_env), true);
	else if (ft_strncmp(name, "exit", 5) == 0)
		return (ft_exe_exit(stream), true);
	return (false);
}

// Checks if the command is in the evnp PATH.
static char	*ft_cmd_exists(t_list *stream, char **copy_env)
{
	int		i;
	char	*path;
	char	**try_paths;
	int		env_pos;

	if (ft_env_exists("PATH", copy_env) == false)
		return (NULL);
	env_pos = find_envp("PATH", copy_env);
	try_paths = ft_split(&(copy_env[env_pos])[5], ':');
	if (!try_paths)
		return (NULL);
	i = 0;
	while (try_paths[i])
	{
		path = ft_strjoin_delimit(try_paths[i], '/', TOKEN->arg[0]);
		printf("Schronk: %s\n", path);
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

static char	*ft_str_tolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

void	ft_execute_command(t_list *stream, char ***copy_env)
{
	char	*path;

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
			ft_error_cmd("Command not found\n", TOKEN->arg[0]);
		else
			execve(path, TOKEN->arg, *copy_env);
	}
	if (TOKEN->fd_out != 1)
		close(TOKEN->fd_out);
	return ;
}
