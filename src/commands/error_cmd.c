/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:08:01 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/19 12:45:38 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_cmd(char *message, char *name)
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
	write(STDERR_FILENO, "\n", 1);
}
