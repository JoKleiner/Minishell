/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:37:56 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/15 16:55:26 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_change_currentpwd(char ***copy_env)
{
	char	*pwd_envvar;
	char	**temp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_error_cmd("Malloc failed.", "cd"));
	pwd_envvar = ft_strjoin("PWD=", cwd);
	if (!pwd_envvar)
		return (free(cwd), ft_error_cmd("Malloc failed.", "cd"));
	if (ft_env_exists("PWD", *copy_env) == true)
		temp = ft_update_envvar(pwd_envvar, "PWD", *copy_env);
	else
		temp = ft_add_envvar(pwd_envvar, *copy_env);
	free(pwd_envvar);
	if (!temp)
		return (free(cwd), ft_error_cmd("Malloc failed.", "cd"));
	free_strarr(*copy_env);
	*copy_env = temp;
	free(cwd);
}

static void	ft_change_oldpwd(char *cwd, char ***copy_env)
{
	char	*pwd_envvar;
	char	**temp;

	pwd_envvar = ft_strjoin("OLDPWD=", cwd);
	if (!pwd_envvar)
		return (free(cwd), ft_error_cmd("Malloc failed.", "cd"));
	if (ft_env_exists("OLDPWD", *copy_env) == true)
		temp = ft_update_envvar(pwd_envvar, "OLDPWD", *copy_env);
	else
		temp = ft_add_envvar(pwd_envvar, *copy_env);
	free(pwd_envvar);
	if (!temp)
		return (free(cwd), ft_error_cmd("Malloc failed.", "cd"));
	free_strarr(*copy_env);
	*copy_env = temp;
	free(cwd);
}

void	ft_exe_cd(t_list *stream, char ***copy_env)
{
	int		env_pos;
	char	*temp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_error_cmd("Malloc failed.", "cd"));
	if (TOKEN->arg[1] != NULL && TOKEN->arg[2] != NULL)
		return (free(cwd), ft_error_cmd("Too many arguments!", "cd"));
	if (!TOKEN->arg[1])
	{
		if (ft_env_exists("HOME", *copy_env) == false)
			return (free(cwd), ft_error_cmd("HOME not set.", "cd"));
		env_pos = find_envp("HOME", *copy_env);
		temp = ft_strnstr((*copy_env)[env_pos], "=",
				ft_strlen((*copy_env)[env_pos]));
		if (!temp || !temp[1])
			return (free(cwd), ft_error_cmd("HOME not set.", "cd"));
		temp++;
		if (chdir(temp) == -1)
			return (free(cwd), ft_error_cmd("No valid directory.", "cd"));
	}
	else if (chdir(TOKEN->arg[1]) == -1)
		return (free(cwd), ft_error_cmd("Couldn't change directory.", "cd"));
	ft_change_currentpwd(copy_env);
	ft_change_oldpwd(cwd, copy_env);
}
