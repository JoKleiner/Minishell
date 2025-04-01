/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:54 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/01 20:15:09 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_fun(t_token *stream, char exnum)
{
	free_stream(stream);
	exit(exnum);
}

int	ft_exe_exit(t_token *stream)
{
	if (isatty(STDIN_FILENO) && stream->fd_out == STDOUT_FILENO)
		write(STDOUT_FILENO, "exit\n", 5);
	if (stream->arg[1])
	{
		if ((ft_isdigit_str_plusmin(stream->arg[1]) == 1
				&& stream->arg[1][0] != '\0'))
		{
			if (stream->arg[2])
			{
				write(2, "Error: exit: too many arguments!\n", 33);
				exit_fun(stream, 1);
			}
			else
				exit_fun(stream, (unsigned char)atoi(stream->arg[1]));
		}
		else
		{
			ft_error("exit: numeric argument required", stream->arg[1]);
			exit_fun(stream, 2);
		}
	}
	else
		exit_fun(stream, return_value(0, false));
	return (96);
}
