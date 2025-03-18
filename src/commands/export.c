/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:38:19 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/18 17:45:39 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_write_envvar(char *str, int fd_out)
{
	bool	equal_sign;
	int		i;

	write(fd_out, "declare -x ", 11);
	i = 0;
	equal_sign = false;
	while (str[i])
	{
		write(fd_out, &str[i], 1);
		if (str[i] == '=')
		{
			if (equal_sign == false)
				write(fd_out, "\"", 1);
			equal_sign = true;
		}
		i++;
	}
	if (equal_sign == true)
		write(fd_out, "\"", 1);
	write(fd_out, "\n", 1);
}

static void	ft_export_empty(t_list *stream, char ***copy_env)
{
	int		i;
	char	**temp;

	i = 0;
	temp = ft_strarrdup_sort(*copy_env);
	if (!temp)
		return (ft_error_cmd("Malloc failed.", "export"));
	while (temp[i])
	{
		if (ft_str_same("LINES=", temp[i], 6) == false
			&& ft_str_same("COLUMNS=", temp[i], 8) == false)
		{
			ft_write_envvar(temp[i], TOKEN->fd_out);
		}
		i++;
	}
	free_strarr(temp);
}

static char	**ft_env_change(char *arg, char *name, char ***copy_env)
{
	char	**temp;

	if (name == NULL)
		temp = ft_add_envvar(arg, *copy_env);
	else
		temp = ft_update_envvar(arg, name, *copy_env);
	if (!(temp))
		return (NULL);
	free_strarr(*copy_env);
	return (temp);
}

// Executes export
void	ft_exe_export(t_list *stream, char ***copy_env)
{
	int		i;
	char	**temp;
	char	**env_name;

	if (!TOKEN->arg[1])
		return (ft_export_empty(stream, copy_env));
	i = 0;
	while (TOKEN->arg[i + 1])
	{
		if (ft_valid_arg(TOKEN->arg[i + 1]) == true)
		{
			env_name = ft_split(TOKEN->arg[i + 1], '=');
			if (!env_name)
				return (ft_error_cmd("Malloc failed.", "export"));
			if (ft_env_exists(env_name[0], *copy_env) == false)
				temp = ft_env_change(TOKEN->arg[i + 1], NULL, copy_env);
			else
				temp = ft_env_change(TOKEN->arg[i + 1], env_name[0], copy_env);
			free_strarr(env_name);
			if (!temp)
				return (ft_error_cmd("Malloc failed.", "export"));
			*copy_env = temp;
		}
		i++;
	}
}
