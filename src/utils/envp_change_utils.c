/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_change_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:33:30 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/18 17:46:12 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_add_envvar(char *arg, char **copy_env)
{
	char	**dest;
	int		i;
	int		len;

	len = ft_strarrlen(copy_env);
	dest = malloc(sizeof(char *) * (len + 2));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = ft_strdup(copy_env[i]);
		if (!dest[i])
			return (free_strarr(dest), NULL);
		i++;
	}
	dest[i] = ft_strdup(arg);
	if (!dest[i])
		return (free_strarr(dest), NULL);
	dest[i + 1] = NULL;
	return (dest);
}

char	**ft_rm_envvar(char *arg, char **copy_env)
{
	char	**dest;
	int		i;
	int		y;
	int		len;

	len = ft_strarrlen(copy_env);
	dest = malloc(sizeof(char *) * (len));
	if (!dest)
		return (NULL);
	i = 0;
	y = 0;
	while (copy_env[i])
	{
		if (ft_str_same(copy_env[i], arg, ft_strlen(arg)) == false)
		{
			dest[y] = ft_strdup(copy_env[i]);
			if (!dest[y])
				return (free_strarr(dest), NULL);
			y++;
		}
		i++;
	}
	dest[y] = NULL;
	return (dest);
}

char	**ft_update_envvar(char *arg, char *name, char **copy_env)
{
	char	**dest;
	int		i;
	int		env_pos;

	env_pos = find_envp(name, copy_env);
	dest = malloc(sizeof(char *) * (ft_strarrlen(copy_env) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (copy_env[i])
	{
		if (i == env_pos)
			dest[i] = ft_strdup(arg);
		else
			dest[i] = ft_strdup(copy_env[i]);
		if (!dest[i])
			return (free_strarr(dest), NULL);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
