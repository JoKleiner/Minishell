/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:38:19 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/11 10:36:48 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_copy_env(void)
{
	char	**sorted_env;
	int		i;

	i = 0;
	while (environ[i])
		i++;
	sorted_env = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		sorted_env[i] = ft_strdup(environ[i]);
		if (!sorted_env[i])
			exit(0);
		i++;
	}
	return (sorted_env);
}
static char	**ft_sort_env(char **sorted_env)
{
	int		i;
	char	*temp;
	bool	change;

	change = true;
	while (change == true)
	{
		i = 1;
		change = false;
		while (sorted_env[i])
		{
			if (0 < ft_strncmp(sorted_env[i - 1], sorted_env[i],
					ft_strlen(sorted_env[i])))
			{
				temp = sorted_env[i - 1];
				sorted_env[i - 1] = sorted_env[i];
				sorted_env[i] = temp;
				change = true;
			}
			i++;
		}
	}
	if (!sorted_env)
		return (NULL);
	return (sorted_env);
}

void	ft_exe_export(t_list *stream)
{
	char	**sorted_env;
	int		i;

	if (!TOKEN->arg[1])
	{
		sorted_env = ft_copy_env();
		sorted_env = ft_sort_env(sorted_env);
		if (!sorted_env)
			exit(0);
		i = 0;
		while (sorted_env[i])
		{
			if (ft_str_same("LINES=", sorted_env[i], 6) == false
				&& ft_str_same("COLUMNS=", sorted_env[i], 8) == false)
				printf("declare -x %s\n", sorted_env[i]);
			i++;
		}
	}
}
