/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:38:06 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/19 16:13:49 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exe_pwd(t_list *stream)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_error_cmd("Couldn't get current working directory!", "pwd");
		return(1);
	}
	write(TOKEN->fd_out, path, ft_strlen(path));
	write(TOKEN->fd_out, "\n", 1);
	return (free(path), 0);
}
