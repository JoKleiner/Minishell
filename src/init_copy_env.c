/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_copy_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:45:23 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/20 11:51:08 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**ft_init_envvar_helper(char **copy_env)
{
	char	**temparr;
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strchr(copy_env[find_envp("SHLVL", copy_env)], '=');
	tmp1 = ft_itoa(ft_atoi(++tmp1) + 1);
	if (!tmp1)
		return (free_strarr(copy_env), NULL);
	tmp2 = ft_strjoin("SHLVL=", tmp1);
	if (!tmp2)
		return (free(tmp1), free_strarr(copy_env), NULL);
	temparr = ft_update_envvar(tmp2, "SHLVL", copy_env);
	free(tmp1);
	free(tmp2);
	return (temparr);
}

char	**ft_init_envvars(void)
{
	char	**copy_env;
	char	**temparr;

	copy_env = ft_strarrdup(environ);
	if (!copy_env)
		return (NULL);
	if (ft_env_exists("SHLVL", copy_env) == true)
	{
		temparr = ft_init_envvar_helper(copy_env);
	}
	else
	{
		temparr = ft_add_envvar("SHLVL=1", copy_env);
	}
	free_strarr(copy_env);
	if (!temparr)
		return (NULL);
	copy_env = temparr;
	return (copy_env);
}
