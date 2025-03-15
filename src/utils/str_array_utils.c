/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:29:49 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/15 15:21:19 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Calculates the length of a double pointer char **sstr.
int	ft_strarrlen(char **sstr)
{
	int	sstrlen;

	if (!sstr)
		return (0);
	sstrlen = 0;
	while (sstr[sstrlen] != NULL)
		sstrlen++;
	return (sstrlen);
}

// Copies a char **sstr and return it.
char	**ft_strarrdup(char **sstr)
{
	char	**copy_env;
	int		i;

	if (!sstr)
		return (sstr);
	i = ft_strarrlen(sstr);
	copy_env = malloc(sizeof(char *) * (i + 1));
	if (!copy_env)
		return (NULL);
	i = 0;
	while (sstr[i])
	{
		copy_env[i] = ft_strdup(sstr[i]);
		if (!copy_env[i])
		{
			free_strarr(copy_env);
			return (NULL);
		}
		i++;
	}
	copy_env[i] = NULL;
	return (copy_env);
}

// Uses ft_strarrdup and sorts the strings in alphabetical order.
char	**ft_strarrdup_sort(char **sstr)
{
	int		i;
	bool	change;
	char	*temp;
	char	**sort_sstr;

	if (!sstr)
		return (sstr);
	sort_sstr = ft_strarrdup(sstr);
	if (!sort_sstr)
		return (NULL);
	change = true;
	while (change == true)
	{
		i = 1;
		change = false;
		while (sort_sstr[i])
		{
			if (0 < ft_strncmp(sort_sstr[i - 1], sort_sstr[i],
					ft_strlen(sort_sstr[i])))
			{
				temp = sort_sstr[i - 1];
				sort_sstr[i - 1] = sort_sstr[i];
				sort_sstr[i] = temp;
				change = true;
			}
			i++;
		}
	}
	return (sort_sstr);
}
