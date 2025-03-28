/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:29 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 12:13:24 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exe_unset(t_list *stream, char ***copy_env)
{
	int		i;
	char	**temp;

	if (!TOKEN->arg[1])
		return (0);
	i = 1;
	while (TOKEN->arg[i])
	{
		{
			if (ft_env_exists(TOKEN->arg[i], *copy_env) == true)
			{
				temp = ft_rm_envvar(TOKEN->arg[i], *copy_env);
				if (!(temp))
					return (ft_errmal("Error: unset:"), 1);
				free_strarr(*copy_env);
				*copy_env = temp;
			}
		}
		i++;
	}
	return (0);
}
