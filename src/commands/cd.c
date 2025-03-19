/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:37:56 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/19 12:25:24 by mpoplow          ###   ########.fr       */
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
		return (ft_errmal("Error: cd:"));
	pwd_envvar = ft_strjoin("PWD=", cwd);
	if (!pwd_envvar)
		return (free(cwd), ft_errmal("Error: cd:"));
	if (ft_env_exists("PWD", *copy_env) == true)
		temp = ft_update_envvar(pwd_envvar, "PWD", *copy_env);
	else
		temp = ft_add_envvar(pwd_envvar, *copy_env);
	free(pwd_envvar);
	if (!temp)
		return (free(cwd), ft_errmal("Error: cd:"));
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
		return (free(cwd), ft_errmal("Error: cd:"));
	if (ft_env_exists("OLDPWD", *copy_env) == true)
		temp = ft_update_envvar(pwd_envvar, "OLDPWD", *copy_env);
	else
		temp = ft_add_envvar(pwd_envvar, *copy_env);
	free(pwd_envvar);
	if (!temp)
		return (free(cwd), ft_errmal("Error: cd:"));
	free_strarr(*copy_env);
	*copy_env = temp;
	free(cwd);
}

static bool	ft_cd_home(char *cwd, char ***copy_env)
{
	int		env_pos;
	char	*temp;

	if (ft_env_exists("HOME", *copy_env) == false)
		return (free(cwd), ft_error_cmd("HOME not set.", "cd"), 0);
	env_pos = find_envp("HOME", *copy_env);
	temp = ft_strnstr((*copy_env)[env_pos], "=",
			ft_strlen((*copy_env)[env_pos]));
	if (!temp || !temp[1])
		return (free(cwd), ft_error_cmd("HOME not set.", "cd"), 0);
	temp++;
	if (chdir(temp) == -1)
		return (free(cwd), ft_error_cmd("No valid directory.", "cd"), 0);
	return (true);
}

static bool	ft_cd_minus(char *cwd, char ***copy_env)
{
	int		env_pos;
	char	*temp;

	if (ft_env_exists("OLDPWD", *copy_env) == false)
		return (free(cwd), ft_error_cmd("OLDPWD not set.", "cd"), 0);
	env_pos = find_envp("OLDPWD", *copy_env);
	temp = ft_strnstr((*copy_env)[env_pos], "=",
			ft_strlen((*copy_env)[env_pos]));
	if (!temp || !temp[1])
		return (free(cwd), ft_error_cmd("OLDPWD not set.", "cd"), 0);
	temp++;
	if (chdir(temp) == -1)
		return (free(cwd), ft_error_cmd("No valid directory.", "cd"), 0);
	printf("%s\n", temp);
	return (true);
}

void	ft_exe_cd(t_list *stream, char ***copy_env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_errmal("Error: cd:"));
	if (TOKEN->arg[1] != NULL && TOKEN->arg[2] != NULL)
		return (free(cwd), ft_error_cmd("Too many arguments!", "cd"));
	else if (!TOKEN->arg[1])
	{
		if (ft_cd_home(cwd, copy_env) == false)
			return ;
	}
	else if (TOKEN->arg[1][0] == '-' && TOKEN->arg[1][1] == '\0')
	{
		if (ft_cd_minus(cwd, copy_env) == false)
			return ;
	}
	else if (chdir(TOKEN->arg[1]) == -1)
		return (free(cwd),
				ft_error_cmd("Couldn't change directory.", "cd"));
	ft_change_currentpwd(copy_env);
	ft_change_oldpwd(cwd, copy_env);
}
