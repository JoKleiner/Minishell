/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:38:19 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/13 13:22:56 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_add_envvar(char *arg, char **copy_env)
{
	char	**dest;
	int		i;
	int		len;

	len = ft_strstrlen(copy_env);
	dest = malloc(sizeof(char *) * (len + 2));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = ft_strdup(copy_env[i]);
		if (!dest[i])
			return (free_strstr(dest), NULL);
		i++;
	}
	dest[i] = ft_strdup(arg);
	if (!dest[i])
		return (free_strstr(dest), NULL);
	dest[i + 1] = NULL;
	return (dest);
}

static void	ft_export_empty(char ***copy_env)
{
	int		i;
	char	**temp;

	i = 0;
	temp = ft_strstrdup_sort(*copy_env);
	if (!temp)
		return (ft_error_cmd("Malloc failed.", "export"));
	while (temp[i])
	{
		if (ft_str_same("LINES=", temp[i], 6) == false
			&& ft_str_same("COLUMNS=", temp[i], 8) == false)
			printf("declare -x %s\n", temp[i]);
		i++;
	}
	free_strstr(temp);
}

void	ft_exe_export(t_list *stream, char ***copy_env)
{
	int		i;
	char	**temp;

	if (!TOKEN->arg[1])
	{
		ft_export_empty(copy_env);
		return ;
	}
	i = 0;
	while (TOKEN->arg[i + 1])
	{
		temp = ft_add_envvar(TOKEN->arg[i + 1], *copy_env);
		if (!(temp))
			return (ft_error_cmd("Malloc failed.", "export"));
		free_strstr(*copy_env);
		*copy_env = temp;
		i++;
	}
}
