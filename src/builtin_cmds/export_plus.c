/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:37:07 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/26 11:13:50 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_expplus_new(char **arg, char *name)
{
	char	*dest;

	dest = ft_strjoin(name, ft_strchr(*arg, '='));
	if (!dest)
		return (NULL);
	free(*arg);
	return (dest);
}

static char	*ft_expplus_change(char **arg, char *name, char ***copy_env)
{
	char	*dest;
	char	*temp;

	temp = ft_strchr(*arg, '=');
	if(!temp)
		return(NULL);
	temp++;
	dest = ft_strjoin((*copy_env)[find_envp(name, *copy_env)], temp);
	if (!dest)
		return (NULL);
	free(*arg);
	return (dest);
}

int	ft_export_plus(char ***copy_env, char **arg)
{
	char	**env_name;
	int		i;

	env_name = ft_split(*arg, '=');
	if (!env_name)
		return (ft_error("Malloc failed.", "export"), 12);
	i = 0;
	while (env_name[0][i++])
		if (env_name[0][i] == '+')
			env_name[0][i] = '\0';
	if (ft_env_exists(env_name[0], *copy_env) == false)
	{
		*arg = ft_expplus_new(arg, env_name[0]);
		if (!(*arg))
			return (free_strarr(env_name), ft_error("Malloc failed.", "export"),
				12);
	}
	else
	{
		*arg = ft_expplus_change(arg, env_name[0], copy_env);
		if (!(*arg))
			return (free_strarr(env_name), ft_error("Malloc failed.", "export"),
				12);
	}
	return (free_strarr(env_name), 0);
}
