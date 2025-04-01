/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:29:00 by mpoplow           #+#    #+#             */
/*   Updated: 2025/04/01 14:34:32 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_builtin_helper(char *name, t_token *stream, char ***copy_env)
{
	if (ft_strncmp(name, "echo", 5) == 0)
	{
		stream->error = ft_exe_echo(stream);
		return (true);
	}
	else if (ft_strncmp(name, "pwd", 4) == 0)
	{
		stream->error = ft_exe_pwd(stream);
		return (true);
	}
	else if (ft_strncmp(name, "exit", 5) == 0)
	{
		free_strarr(*copy_env);
		stream->error = ft_exe_exit(stream);
		return (true);
	}
	else if (ft_strncmp(name, "export", 8) == 0)
	{
		stream->error = ft_exe_export(stream, copy_env);
		return (true);
	}
	return (false);
}

// Checks if the command is a self-made command
bool	ft_builtin_cmd(char *name, t_token *stream, char ***copy_env)
{
	if (ft_strncmp(name, "cd", 3) == 0)
	{
		stream->error = ft_exe_cd(stream, copy_env);
		return (true);
	}
	else if (ft_strncmp(name, "env", 4) == 0)
	{
		stream->error = ft_exe_env(stream, *copy_env);
		return (true);
	}
	else if (ft_strncmp(name, "unset", 6) == 0)
	{
		stream->error = ft_exe_unset(stream, copy_env);
		return (true);
	}
	if (ft_builtin_helper(name, stream, copy_env) == true)
		return (true);
	else
		return (false);
}
