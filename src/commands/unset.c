/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:29 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/18 17:51:17 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exe_unset(t_list *stream, char ***copy_env)
{
	int		i;
	char	**temp;

	if (!TOKEN->arg[1])
		return ;
	i = 1;
	while (TOKEN->arg[i])
	{
		if (ft_strchr(TOKEN->arg[i], '=') != 0)
			return (ft_error_cmd("not a valid identifier", "unset"));
		else
		{
			if (ft_env_exists(TOKEN->arg[i], *copy_env) == true)
			{
				temp = ft_rm_envvar(TOKEN->arg[i], *copy_env);
				if (!(temp))
					return (ft_error_cmd("Malloc failed.", "unset"));
				free_strarr(*copy_env);
				*copy_env = temp;
			}
		}
		i++;
	}
}
