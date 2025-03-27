/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:54 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/27 22:12:38 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exe_exit(t_list *stream)
{
	if (isatty(STDOUT_FILENO))
		write(STDOUT_FILENO, "exit\n", 5);
	if (TOKEN->arg[1])
	{
		if ((ft_isdigit_str_plusmin(TOKEN->arg[1]) == 1
				&& TOKEN->arg[1][0] != '\0'))
			if (TOKEN->arg[2])
			{
				write(2, "Error: exit: too many arguments!\n", 33);
				exit(1);
			}
			else
				exit((unsigned char)atoi(TOKEN->arg[1]));
		else
		{
			ft_error("exit: numeric argument required", TOKEN->arg[1]);
			exit(2);
		}
	}
	else
		exit(return_value(0, false));
}
