/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:13:05 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/07 10:27:17 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// // Checks if the command is a self-made command
// static bool	ft_selfmade_cmd(t_data *data, t_list	*stream)
// {
// 	if (ft_strncmp(TOKEN->arg[0], "echo", 4) == 0)
// 		return (ft_exe_echo(arglist), true);
// 	else if (ft_strncmp(TOKEN->arg[0], "cd", 2) == 0)
// 		return (ft_exe_cd(arglist), true);
// 	else if (ft_strncmp(TOKEN->arg[0], "pwd", 3) == 0)
// 		return (ft_exe_pwd(arglist), true);
// 	else if (ft_strncmp(TOKEN->arg[0], "export", 7) == 0)
// 		return (ft_exe_export(arglist), true);
// 	else if (ft_strncmp(TOKEN->arg[0], "unset", 5) == 0)
// 		return (ft_exe_unset(arglist), true);
// 	else if (ft_strncmp(TOKEN->arg[0], "env", 3) == 0)
// 		return (ft_exe_env(arglist), true);
// 	else if (ft_strncmp(TOKEN->arg[0], "exit", 4) == 0)
// 		return (ft_exe_exit(arglist), true);
// 	return (false);
// }

// // Checks if the command is in the evnp PATH.
// static char	*ft_cmd_exists(t_data *data, t_list *stream)
// {
// 	int		i;

// 	data->try_paths = ft_split(environ[4], ':');
// 	if (!data->try_paths)
// 		exit(1);
// 	i = 0;
// 	while (data->try_paths[i])
// 	{
// 		data->path = ft_strjoin(data->try_paths[i], TOKEN->arg[0]);
// 		if (!data->path)
// 			exit(1);
// 		if (access(data->path, F_OK) == 0)
// 			break ;
// 		i++;
// 		free(data->path);
// 	} 
// 	i = 0;
// 	while (data->try_paths[i])
// 		free(data->try_paths[i++]);
// 	free(data->try_paths);
// 	return (data->path);
// }

// // Executes self-made and builtin commands.
// // Error if command does not exist.
// void	ft_execute_command(t_list	*stream)
// {
// 	t_data data;
		
// 	if (ft_selfmade_cmd(&data, stream) == false)
// 	{
// 		data.path = ft_cmd_exists(&data, stream);
// 		if (data.path != NULL)
// 		{
// 			execve(data.path, TOKEN->arg, environ);
// 			free(data.path);
// 		}
// 		else
// 			printf("Error\nCommand not found\n");
// 	}
// }
