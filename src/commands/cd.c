/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:37:56 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/14 21:11:07 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_change_oldpwd(char *cwd, char **copy_env, t_list *stream)
{
	TOKEN->arg = malloc(3 * sizeof(char *));
	if (!TOKEN->arg)
		return (free(cwd), ft_error_cmd("Malloc failed.", "export"));
	TOKEN->arg[0] = ft_strdup("export");
	TOKEN->arg[1] = ft_strjoin("OLDPWD=", cwd);
	TOKEN->arg[2] = NULL;
	ft_exe_export(stream, &copy_env);
}

void	ft_exe_cd(t_list *stream, char **copy_env)
{
	int		env_pos;
	char	*temp;
	char	*cwd;
	t_list	stream_pwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_error_cmd("Malloc failed.", "export"));
	if (TOKEN->arg[1] != NULL && TOKEN->arg[2] != NULL)
		return (free(cwd), ft_error_cmd("Too many arguments!", "cd"));
	if (!TOKEN->arg[1])
	{
		if (ft_env_exists("HOME", copy_env) == false)
			return (free(cwd), ft_error_cmd("HOME not set.", "cd"));
		env_pos = find_envp("HOME", copy_env);
		temp = ft_strnstr(copy_env[env_pos], "=", ft_strlen(copy_env[env_pos]));
		if (!temp || !temp[1])
			return (free(cwd), ft_error_cmd("HOME not set.", "cd"));
		temp++;
		if (chdir(temp) == -1)
			return (free(cwd), ft_error_cmd("No valid directory.", "cd"));
	}
	else if (chdir(TOKEN->arg[1]) == -1)
		return (free(cwd), ft_error_cmd("Couldn't change directory.", "cd"));
	ft_change_oldpwd(cwd, copy_env, &stream_pwd);
}
