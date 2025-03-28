/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:42:26 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 14:08:21 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_non_accessible(t_token *stream)
{
	if (access(stream->arg[0], F_OK) == 0)
	{
		if (access(stream->arg[0], X_OK) == 0)
			return (false);
		else
		{
			ft_error("permission denied.", stream->arg[0]);
			return (token_err(stream, 126), true);
		}
	}
	else
	{
		if (ft_strchr(stream->arg[0], '/') == NULL)
		{
			ft_error(CMD_NF, stream->arg[0]);
			return (token_err(stream, 127), true);
		}
		else
		{
			ft_error(N_FD, stream->arg[0]);
			return (token_err(stream, 127), true);
		}
	}
}

bool	ft_is_executable(char *arg, t_token *stream, char ***copy_env)
{
	struct stat	file_info;

	if (ft_init_stat(arg, stream, &file_info) == false)
		return (token_err(stream, errno), ft_error("stat failed.", "minishell"),
			true);
	if (ft_isdir(file_info) == true)
	{
		write(2, "minishell: ", 11);
		write(2, arg, ft_strlen(arg));
		write(2, ": Is a directory\n", 17);
		return (token_err(stream, 126), true);
	}
	if (ft_strchr(arg, '/') == NULL)
		return (token_err(stream, 127), ft_error(CMD_NF, arg), true);
	if (ft_isregfile(file_info) == true)
	{
		stream->error = ft_execute_cmd_fork(arg, stream, copy_env);
		return (true);
	}
	else
		return (token_err(stream, 127), ft_error(N_FD, arg), true);
}
