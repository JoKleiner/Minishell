/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:29 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/28 14:15:53 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exe_unset(t_token *stream, char ***copy_env)
{
	int		i;
	char	**temp;

	if (!stream->arg[1])
		return (0);
	i = 1;
	while (stream->arg[i])
	{
		{
			if (ft_env_exists(stream->arg[i], *copy_env) == true)
			{
				temp = ft_rm_envvar(stream->arg[i], *copy_env);
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
