/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:37:56 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/25 15:11:46 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_change_currentpwd(char ***copy_env)
{
	char	*pwd_envvar;
	char	**temp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_errmal("Error: cd:"), 12);
	pwd_envvar = ft_strjoin("PWD=", cwd);
	if (!pwd_envvar)
		return (free(cwd), ft_errmal("Error: cd:"), 12);
	if (ft_env_exists("PWD", *copy_env) == true)
		temp = ft_update_envvar(pwd_envvar, "PWD", *copy_env);
	else
		temp = ft_add_envvar(pwd_envvar, *copy_env);
	free(pwd_envvar);
	if (!temp)
		return (free(cwd), ft_errmal("Error: cd:"), 12);
	free_strarr(*copy_env);
	*copy_env = temp;
	return (free(cwd), 0);
}

static int	ft_change_oldpwd(char *cwd, char ***copy_env)
{
	char	*pwd_envvar;
	char	**temp;

	pwd_envvar = ft_strjoin("OLDPWD=", cwd);
	if (!pwd_envvar)
		return (free(cwd), ft_errmal("Error: cd:"), 12);
	if (ft_env_exists("OLDPWD", *copy_env) == true)
		temp = ft_update_envvar(pwd_envvar, "OLDPWD", *copy_env);
	else
		temp = ft_add_envvar(pwd_envvar, *copy_env);
	free(pwd_envvar);
	if (!temp)
		return (free(cwd), ft_errmal("Error: cd:"), 12);
	free_strarr(*copy_env);
	*copy_env = temp;
	return (free(cwd), 0);
}

static int	ft_cd_home(char *cwd, char ***copy_env)
{
	int		env_pos;
	char	*temp;

	if (ft_env_exists("HOME", *copy_env) == false)
		return (free(cwd), ft_error("HOME not set.", "cd"), 1);
	env_pos = find_envp("HOME", *copy_env);
	temp = ft_strnstr((*copy_env)[env_pos], "=",
			ft_strlen((*copy_env)[env_pos]));
	if (!temp || !temp[1])
		return (free(cwd), ft_error("HOME not set.", "cd"), 12);
	temp++;
	if (chdir(temp) == -1)
		return (free(cwd), ft_error("No valid directory.", "cd"), errno);
	return (0);
}

static int	ft_cd_minus(char *cwd, char ***copy_env)
{
	int		env_pos;
	char	*temp;

	if (ft_env_exists("OLDPWD", *copy_env) == false)
		return (free(cwd), ft_error("OLDPWD not set.", "cd"), 1);
	env_pos = find_envp("OLDPWD", *copy_env);
	temp = ft_strnstr((*copy_env)[env_pos], "=",
			ft_strlen((*copy_env)[env_pos]));
	if (!temp || !temp[1])
		return (free(cwd), ft_error("OLDPWD not set.", "cd"), 12);
	temp++;
	if (chdir(temp) == -1)
		return (free(cwd), ft_error("No valid directory.", "cd"), errno);
	printf("%s\n", temp);
	return (0);
}

int	ft_exe_cd(t_list *stream, char ***copy_env)
{
	char	*cwd;
	int		err;

	err = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_errmal("Error: cd:"), 12);
	if (TOKEN->arg[1] != NULL && TOKEN->arg[2] != NULL)
		return (free(cwd), ft_error("Too many arguments!", "cd"), errno);
	else if ((TOKEN->arg[1][0] == '-' && TOKEN->arg[1][1] == '\0')
			|| !TOKEN->arg[1])
	{
		if (!TOKEN)
			err = ft_cd_home(cwd, copy_env);
		else
			err = ft_cd_minus(cwd, copy_env);
		if (err != 0)
			return (err);
	}
	else if (chdir(TOKEN->arg[1]) == -1)
		return (free(cwd), ft_error("Couldn't change dir.", "cd"), errno);
	if (ft_change_currentpwd(copy_env) == 12 || ft_change_oldpwd(cwd,
			copy_env) == 12)
		return (12);
	return (0);
}
