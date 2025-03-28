/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:37:41 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 14:08:21 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_flag_n(t_token *stream, int *i)
{
	int		char_num;
	bool	isflag_n;

	isflag_n = false;
	while (stream->arg[*i])
	{
		char_num = 0;
		if (stream->arg[*i][char_num] != '-')
			return (isflag_n);
		if (stream->arg[*i][char_num + 1] == '\0')
			return (isflag_n);
		char_num++;
		while (stream->arg[*i][char_num])
		{
			if (stream->arg[*i][char_num] != 'n')
				return (isflag_n);
			char_num++;
		}
		isflag_n = true;
		(*i)++;
	}
	return (isflag_n);
}

int	ft_exe_echo(t_token *stream)
{
	int		i;
	bool	isflag_n;

	i = 1;
	isflag_n = ft_flag_n(stream, &i);
	while (stream->arg[i])
	{
		write(stream->fd_out, stream->arg[i], ft_strlen(stream->arg[i]));
		i++;
		if (stream->arg[i])
			write(stream->fd_out, " ", 1);
	}
	if (isflag_n == false)
		write(stream->fd_out, "\n", 1);
	return (0);
}
