/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_check_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:45:41 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/19 12:21:50 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Returns true if the env is found in copy_env
bool	ft_env_exists(char *arg, char **copy_env)
{
	int	i;

	i = 0;
	while (copy_env[i])
	{
		if (ft_str_same(arg, copy_env[i], ft_strlen(arg)) == true)
			return (true);
		i++;
	}
	return (false);
}

// Returns position of the env in copy_env.
int	find_envp(char *str, char **copy_env)
{
	int	u;

	u = 0;
	while (copy_env[u])
	{
		if (ft_strncmp(str, copy_env[u], ft_strlen(str)) == 0)
			break ;
		u++;
	}
	return (u);
}

int	env_char(char input)
{
	if (input >= 'a' && input <= 'z')
		return (1);
	if (input >= 'A' && input <= 'Z')
		return (1);
	if (input >= '0' && input <= '9')
		return (1);
	if (input == '_')
		return (1);
	return (0);
}
