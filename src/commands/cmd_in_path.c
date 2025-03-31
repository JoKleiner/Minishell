/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_in_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:40:09 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/31 17:35:17 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_cmd_helper(char **try_paths, t_token *stream, char ***copy_env)
{
	char	*path;
	int		i;

	i = 0;
	while (try_paths[i])
	{
		path = ft_strjoin_delimit(try_paths[i], '/', stream->arg[0]);
		if (!(path))
			return (mem_fail(stream), true);
		if (access(path, X_OK) == 0)
			return (stream->error = ft_execute_cmd_fork(path, stream, copy_env),
				free(path), true);
		free(path);
		i++;
	}
	return (false);
}

bool	ft_cmd_in_path(t_token *stream, char ***copy_env)
{
	char	**try_paths;
	int		env_pos;
	bool	retval;

	if (stream->arg[0][0] == '.' || stream->arg[0][0] == '/')
		return (false);
	if (ft_env_exists("PATH", *copy_env) == false)
		return (false);
	env_pos = find_envp("PATH", *copy_env);
	try_paths = ft_split(&((*copy_env)[env_pos][5]), ':');
	if (!try_paths)
		return (mem_fail(stream), true);
	retval = ft_cmd_helper(try_paths, stream, copy_env);
	return (free_strarr(try_paths), retval);
}
