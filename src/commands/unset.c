/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:29 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/14 10:37:13 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_rm_envvar(char *arg, char **copy_env)
{
	char	**dest;
	int		i;
	int		y;
	int		len;

	len = ft_strstrlen(copy_env);
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
				return (free_strstr(dest), NULL);
			y++;
		}
		i++;
	}
	dest[y] = NULL;
	return (dest);
}

void	ft_exe_unset(t_list *stream, char ***copy_env)
{
	int		i;
	char	**temp;

	if (!TOKEN->arg[1])
		return ;
	i = 1;
	while (TOKEN->arg[i])
	{
		if (ft_strchr(TOKEN->arg[i], '=') != 0)
			printf("Error: unset: %s: not a valid identifier\n", TOKEN->arg[i]);
		else
		{
			if (ft_env_exists(TOKEN->arg[i], *copy_env) == true)
			{
				temp = ft_rm_envvar(TOKEN->arg[i], *copy_env);
				if (!(temp))
					return (ft_error_cmd("Malloc failed.", "unset"));
				free_strstr(*copy_env);
				*copy_env = temp;
			}
		}
		i++;
	}
}
