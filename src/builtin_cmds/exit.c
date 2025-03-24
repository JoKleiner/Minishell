/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:54 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/23 17:08:16 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (0 == ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exe_exit(t_list *stream)
{
	printf("exit\n");
	if (TOKEN->arg[1])
	{
		if (TOKEN->arg[2])
		{
			write(2, "Error: exit: too many arguments!\n", 33);
			exit(1);
		}
		else
		{
			if (ft_isdigit_str(TOKEN->arg[1]) == 1
				&& ft_strlen(TOKEN->arg[1]) <= 19)
				exit(atoi(TOKEN->arg[1]));
			else
			{
				ft_error_cmd("exit: numeric argument required", TOKEN->arg[1]);
				exit(1);
			}
		}
	}
	else
		exit(0);
}
