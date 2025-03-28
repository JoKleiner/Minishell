/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:08:01 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 14:08:21 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error(char *message, char *name)
{
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, name, ft_strlen(name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

void	ft_errmal(char *name)
{
	write(STDERR_FILENO, "Error: ", 7);
	perror(name);
	// write(STDERR_FILENO, "\n", 1);
}

void	mem_fail(t_token *stream)
{
	ft_errmal("malloc failed");
	stream->error = ENOMEM;
}

void	ft_closefdout(t_token *stream)
{
	if (stream->fd_out != 1)
		close(stream->fd_out);
}

void	token_err(t_token *stream, int value)
{
	stream->error = value;
}
