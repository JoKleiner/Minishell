/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:54 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 14:08:21 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exe_exit(t_token *stream)
{
	if (isatty(STDOUT_FILENO))
		write(STDOUT_FILENO, "exit\n", 5);
	if (stream->arg[1])
	{
		if ((ft_isdigit_str_plusmin(stream->arg[1]) == 1
				&& stream->arg[1][0] != '\0'))
			if (stream->arg[2])
			{
				write(2, "Error: exit: too many arguments!\n", 33);
				exit(1);
			}
			else
				exit((unsigned char)atoi(stream->arg[1]));
		else
		{
			ft_error("exit: numeric argument required", stream->arg[1]);
			exit(2);
		}
	}
	else
		exit(return_value(0, false));
}
