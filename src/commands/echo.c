/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:37:41 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/19 16:04:44 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_flag_n(t_list *stream, int *i)
{
	int		char_num;
	bool	isflag_n;

	isflag_n = false;
	while (TOKEN->arg[*i])
	{
		char_num = 0;
		if (TOKEN->arg[*i][char_num] != '-')
			return (isflag_n);
		char_num++;
		while (TOKEN->arg[*i][char_num])
		{
			if (TOKEN->arg[*i][char_num] != 'n')
				return (isflag_n);
			char_num++;
		}
		isflag_n = true;
		(*i)++;
	}
	return (isflag_n);
}

int	ft_exe_echo(t_list *stream)
{
	int		i;
	bool	isflag_n;

	i = 1;
	isflag_n = ft_flag_n(stream, &i);
	while (TOKEN->arg[i])
	{
		write(TOKEN->fd_out, TOKEN->arg[i], ft_strlen(TOKEN->arg[i]));
		i++;
		if (TOKEN->arg[i])
			write(TOKEN->fd_out, " ", 1);
	}
	if (isflag_n == false)
		write(TOKEN->fd_out, "\n", 1);
	return(0);
}
