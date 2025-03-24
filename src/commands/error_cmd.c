/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:08:01 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/24 11:20:16 by joklein          ###   ########.fr       */
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

void	mem_fail(t_list *stream)
{
	ft_errmal("Malloc failed.");
	TOKEN->error = ENOMEM;
}
