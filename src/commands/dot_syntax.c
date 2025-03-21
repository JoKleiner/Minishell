/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_syntax.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:54:26 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/21 17:23:59 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_exe_dotslashfile(t_list *stream, char *arg, char ***copy_env)
{
	struct stat	file_info;

	if (access(arg, X_OK) == 0)
	{
		if (stat(arg, &file_info) == -1)
		{
			TOKEN->error = errno;
			return (false);
		}
		if (S_ISREG(file_info.st_mode) == true)
		{
			ft_execute_cmd_fork(arg, stream, copy_env);
			return(false);
		}
	}
	TOKEN->error = 127;
	ft_error_cmd("No such file or directory", arg);
	return(false);
}

// Returns true if command execution should continue, false if not.
bool	ft_dot_syntax(t_list *stream, char ***copy_env)
{
	if (TOKEN->arg[0][0] != '.')
		return (true);
	if (TOKEN->arg[0][1] == '\0' && !TOKEN->arg[1])
	{
		TOKEN->error = 2;
		write(2, "Error: .: filename argument required\n", 37);
		return (write(2, ".: usage: . filename [arguments]\n", 33), false);
	}
	if (ft_strchr(TOKEN->arg[0], '/') == NULL)
	{
		TOKEN->error = 127;
		return (ft_error_cmd("command not found", TOKEN->arg[0]), false);
	}
	if (ft_isdir(TOKEN->arg[0], stream) == true)
	{
		if (TOKEN->error == errno)
			ft_errmal("");
		return (false);
	}
	return (ft_exe_dotslashfile(stream, TOKEN->arg[0], copy_env));
}
