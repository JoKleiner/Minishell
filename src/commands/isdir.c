/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:33:24 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/25 13:54:51 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_isdir(struct stat file_info)
{
	if (S_ISDIR(file_info.st_mode) == true)
		return (true);	
	return (false);
}
// TOKEN->error = 126;
// 		ft_error("Is a directory", arg);


bool	ft_isregfile(struct stat file_info)
{
	if (S_ISREG(file_info.st_mode) == true)
		return (true);
	return (false);
}
// TOKEN->error = 127;
// 		ft_error("Command not found", arg);

bool	ft_init_stat(char *arg, t_list *stream, struct stat *file_info)
{	
	if (stat(arg, file_info) == -1)
		return (token_err(stream, errno), false);
	return (true);
}
