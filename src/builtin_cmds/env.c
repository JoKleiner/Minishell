/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:40 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/25 12:30:07 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Prints the environment.
int	ft_exe_env(t_list *stream, char **copy_env)
{
	int	i;

	(void)copy_env;
	if (TOKEN->arg[1] == NULL)
	{
		i = 0;
		while (copy_env[i])
		{
			if (ft_str_same("LINES=", copy_env[i], 6) == false
				&& ft_str_same("COLUMNS=", copy_env[i], 8) == false)
			{
				if (ft_strstr_num(copy_env[i], "="))
				{
					write(TOKEN->fd_out, copy_env[i], ft_strlen(copy_env[i]));
					write(TOKEN->fd_out, "\n", 1);
				}
			}
			i++;
		}
	}
	else
	{
		return (ft_error("env: Invalid argument\n", TOKEN->arg[1]), 127);
	}
	return (0);
}
