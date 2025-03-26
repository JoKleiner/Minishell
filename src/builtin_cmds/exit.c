/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:54 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/26 15:35:16 by joklein          ###   ########.fr       */
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
	if(isatty(STDOUT_FILENO))
		write(STDOUT_FILENO, "exit\n", 5);
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
				exit((unsigned char)atoi(TOKEN->arg[1]));
			else
			{
				ft_error("exit: numeric argument required", TOKEN->arg[1]);
				exit(2);
			}
		}
	}
	else
		exit(return_value(0, false));
}
