/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:40:29 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/13 13:09:52 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static char	**ft_rm_envvar(char *arg, char **copy_env)
// {
// 	(void)arg;
// 	(void)copy_env;
// }

// void	ft_exe_unset(t_list *stream, char ***copy_env)
// {
// 	int		i;
// 	int		j;
// 	char	**temp;

// 	if (!TOKEN->arg[1])
// 		return ;
// 	i = 1;
// 	while (TOKEN->arg[i])
// 	{
// 		if(ft_strchr(TOKEN->arg[i], '='))
// 			return(ft_error_cmd("", "unset"));
// 		i++;
// 	}
// 	i = 1;
// 	while (TOKEN->arg[i])
// 	{
// 		if (ft_env_exists(TOKEN->arg[i], copy_env))
// 		{
// 			temp = ft_rm_envvar(TOKEN->arg[i], *copy_env);
// 			if (!(temp))
// 				return (ft_error_cmd("Malloc failed.", "unset"));
// 			free_strstr(*copy_env);
// 			*copy_env = temp;
// 		}
// 		i++;
// 	}
// }
