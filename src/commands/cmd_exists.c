/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:40:09 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/21 18:32:28 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_isdir(char *arg, t_list *stream)
{
	struct stat	file_info;

	if (stat(arg, &file_info) == -1)
	{
		TOKEN->error = errno;
		return (true);
	}
	if (S_ISDIR(file_info.st_mode) == true)
	{
		TOKEN->error = 126;
		ft_error_cmd("Is a directory", arg);
		return (true);
	}
	if (S_ISREG(file_info.st_mode) == true)
	{
		TOKEN->error = 127;
		ft_error_cmd("Command not found", arg);
		return (true);
	}
	return (false);
}
static char	*ft_cmd_helper(char **try_paths, t_list *stream)
{
	char	*path;
	int		i;

	i = 0;
	if (access(TOKEN->arg[0], X_OK) == 0)
	{
		if (ft_isdir(TOKEN->arg[0], stream) == true)
			return (NULL);
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
		if (access(path, X_OK) == 0)
			return(path);
		free(path);
		i++;
	}
	ft_error_cmd("Command not found", TOKEN->arg[0]);
	return (path);
}

// Checks if the command is in the evnp PATH.
char	*ft_cmd_exists(t_list *stream, char **copy_env)
{
	char	*path;
	char	**try_paths;
	int		env_pos;

	if (ft_env_exists("PATH", copy_env) == false)
	{
		TOKEN->error = 127;
		return (ft_error_cmd("Command not found", TOKEN->arg[0]), NULL);
	}
	env_pos = find_envp("PATH", copy_env);
	try_paths = ft_split(&(copy_env[env_pos])[5], ':');
	if (!try_paths)
		return (NULL);
	path = ft_cmd_helper(try_paths, stream);
	free_strarr(try_paths);
	return (path);
}
