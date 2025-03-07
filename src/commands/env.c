/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:40 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/07 11:44:40 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Prints the environment.
void	ft_exe_env(t_list *stream)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		write(TOKEN->fd_out, environ[i], ft_strlen(environ[i]));
		write(TOKEN->fd_out, "\n", 1);
		i++;
	}
}
