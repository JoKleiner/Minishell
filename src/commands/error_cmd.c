/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:08:01 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 12:15:27 by mpoplow          ###   ########.fr       */
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
}

void	mem_fail(t_list *stream)
{
	ft_errmal("malloc failed");
	TOKEN->error = ENOMEM;
}

void	ft_closefdout(t_list *stream)
{
	if (TOKEN->fd_out != 1)
		close(TOKEN->fd_out);
}

void	token_err(t_list *stream, int value)
{
	TOKEN->error = value;
}
