/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:08:01 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/14 13:06:41 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_cmd(char *message, char *name)
{
	write(2, "Error: ", 7);
	write(2, name, ft_strlen(name));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}
