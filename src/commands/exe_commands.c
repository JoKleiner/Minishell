/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:13:05 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/05 12:33:47 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdbool.h>

//Cheks if the command is a self-made command
static bool	ft_selfmade_cmd(char *cmd, char **arglist)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (ft_exe_echo(**arglist), true);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (ft_exe_cd(**arglist), true);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (ft_exe_pwd(**arglist), true);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (ft_exe_export(**arglist), true);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (ft_exe_unset(**arglist), true);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (ft_exe_env(**arglist), true);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (ft_exe_exit(**arglist), true);
	return (false);
}

//Checks if the command is in the evnp PATH.
static char	*ft_cmd_exists(t_list *stream, char **envp)
{
	char	**possible_paths;
	char	*path;
	int		i;

	possible_paths = ft_split(envp[4], ':');
	if (!possible_paths)
		exit(1);
	i = 0;
	while (possible_paths[i])
	{
		path = ft_strjoin(possible_paths[i], TOKEN->arg[0]);
		if (!path)
			exit(1);
		if (access(path, F_OK) == 0)
			break ;
		i++;
		free(path);
	}
	i = 0;
	while (possible_paths[i])
		free(possible_paths[i++]);
	free(possible_paths);
	if (!path)
		return (NULL);
	return (path);
}

void	ft_execute_command(t_list *stream_one, char **envp)
{
	char	*path;
	t_list	*stream;

	stream = stream_one;
	if (ft_selfmade_cmd(TOKEN->arg[0], TOKEN->arg) == false)
	{
		path = ft_cmd_exists(stream, envp);
		if (path != NULL)
		{
			execve(path, TOKEN->arg, envp);
		}
		else
			printf("Error\nCommand not found\n");
		free(path);
	}
}
