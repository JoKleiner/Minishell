/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_array_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:29:49 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/27 19:29:47 by mpoplow          ###   ########.fr       */
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

char	*ft_str_tolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
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

static bool	ft_sort_helper(char **sort_sstr, int i)
{
	char	*temp;

	temp = sort_sstr[i - 1];
	sort_sstr[i - 1] = sort_sstr[i];
	sort_sstr[i] = temp;
	return (true);
}

// Uses ft_strarrdup and sorts the strings in alphabetical order.
char	**ft_strarrdup_sort(char **sstr)
{
	int		i;
	bool	change;
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
				change = ft_sort_helper(sort_sstr, i);
			}
			i++;
		}
	}
	return (sort_sstr);
}
