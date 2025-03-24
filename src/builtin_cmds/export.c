/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:38:19 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/24 12:44:39 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_valid_arg(char *str)
{
	int	i;

	if (ft_isdigit(str[0]) == 1)
	{
		write(2, "Error: export: \'", 16);
		write(2, str, ft_strlen(str));
		write(2, "\' not a valid identifier!\n", 26);
		return (1);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		if (env_char(str[i]) == false)
		{
			write(2, "Error: export: \'", 16);
			write(2, str, ft_strlen(str));
			write(2, "\' not a valid identifier!\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
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
int	ft_exe_export(t_list *stream, char ***copy_env)
{
	int		i;
	char	**temp;
	char	**env_name;

	if (!TOKEN->arg[1])
		return (ft_export_empty(stream, copy_env));
	i = 0;
	while (TOKEN->arg[i + 1])
	{
		if (ft_valid_arg(TOKEN->arg[i + 1]) == 0)
		{
			env_name = ft_split(TOKEN->arg[i + 1], '=');
			if (!env_name)
				return (ft_error_cmd("Malloc failed.", "export"), 12);
			if (ft_env_exists(env_name[0], *copy_env) == false)
				temp = ft_env_change(TOKEN->arg[i + 1], NULL, copy_env);
			else
				temp = ft_env_change(TOKEN->arg[i + 1], env_name[0], copy_env);
			free_strarr(env_name);
			if (!temp)
				return (ft_error_cmd("Malloc failed.", "export"), 12);
			*copy_env = temp;
		}
		else
			TOKEN->error = 1;
		i++;
	}
	return(TOKEN->error);
}
