/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:38:19 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 12:12:58 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_not_valid(char *arg)
{
	write(2, "Error: export: \'", 16);
	write(2, arg, ft_strlen(arg));
	write(2, "\' not a valid identifier!\n", 26);
}

int	ft_valid_arg(char *arg, bool *plus)
{
	int	i;

	if (arg[0] == '=' || ft_isdigit(arg[0]) == 1)
		return (ft_not_valid(arg), 1);
	i = 0;
	(*plus) = false;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (0);
		if (env_char(arg[i]) == false)
		{
			if (arg[i] == '+' && arg[i + 1] == '=' && i != 0)
			{
				(*plus) = true;
				return (0);
			}
			return (ft_not_valid(arg), 1);
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

static int	ft_export_normal(char *arg, char ***copy_env)
{
	char	**temp;
	char	**env_name;

	env_name = ft_split(arg, '=');
	if (!env_name)
		return (ft_error("Malloc failed.", "export"), 12);
	if (ft_env_exists(env_name[0], *copy_env) == false)
		temp = ft_env_change(arg, NULL, copy_env);
	else
		temp = ft_env_change(arg, env_name[0], copy_env);
	free_strarr(env_name);
	if (!temp)
		return (ft_error("Malloc failed.", "export"), 12);
	*copy_env = temp;
	return (0);
}

// Executes export
int	ft_exe_export(t_list *stream, char ***copy_env)
{
	int		i;
	int		retval;
	bool	plus;

	if (!TOKEN->arg[1])
		return (ft_export_empty(stream, copy_env));
	i = 1;
	while (TOKEN->arg[i])
	{
		retval = ft_valid_arg(TOKEN->arg[i], &plus);
		if (retval == 0)
		{
			if (plus == true)
				if (ft_export_plus(copy_env, &TOKEN->arg[i]) == 12)
					return (12);
			if (ft_export_normal(TOKEN->arg[i], copy_env) == 12)
				return (12);
		}
		else
			TOKEN->error = retval;
		i++;
	}
	return (TOKEN->error);
}
