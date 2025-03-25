/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_in_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:40:09 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/25 14:31:57 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_cmd_helper(char **try_paths, t_list *stream, char ***copy_env)
{
	char	*path;
	int		i;

	i = 0;
	while (try_paths[i])
	{
		path = ft_strjoin_delimit(try_paths[i], '/', TOKEN->arg[0]);
		if (!(path))
			return (mem_fail(stream), true);
		if (access(path, X_OK) == 0)
			return (ft_execute_cmd_fork(path, stream, copy_env), true);
		free(path);
		i++;
	}
	return (false);
}

bool	ft_cmd_in_path(t_list *stream, char ***copy_env)
{
	char	**try_paths;
	int		env_pos;
	bool	retval;

	if(TOKEN->arg[0][0] == '.' || TOKEN->arg[0][0] == '/')
		return(false);
	if (ft_env_exists("PATH", *copy_env) == false)
		return (false);
	env_pos = find_envp("PATH", *copy_env);
	try_paths = ft_split(&((*copy_env)[env_pos][5]), ':');
	if (!try_paths)
		return (mem_fail(stream), true);
	retval = ft_cmd_helper(try_paths, stream, copy_env);
	return (free_strarr(try_paths), retval);
}
