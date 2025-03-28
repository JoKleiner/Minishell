/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:38:06 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 14:15:31 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exe_pwd(t_token *stream)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_error("Couldn't get current working directory!", "pwd");
		return (12);
	}
	write(stream->fd_out, path, ft_strlen(path));
	write(stream->fd_out, "\n", 1);
	return (free(path), 0);
}
