/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:40 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/02 14:58:22 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Prints the environment.
int	ft_exe_env(t_token *stream, char **copy_env)
{
	int	i;

	(void)copy_env;
	if (stream->arg[1] == NULL)
	{
		i = 0;
		while (copy_env[i])
		{
			if (ft_str_same("LINES=", copy_env[i], 6) == false
				&& ft_str_same("COLUMNS=", copy_env[i], 8) == false)
			{
				if (ft_strstr_num(copy_env[i], "="))
				{
					write(stream->fd_out, copy_env[i], ft_strlen(copy_env[i]));
					write(stream->fd_out, "\n", 1);
				}
			}
			i++;
		}
	}
	else
	{
		return (ft_error("env: Invalid argument", stream->arg[1]), 127);
	}
	return (0);
}
