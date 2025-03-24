/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:43:56 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/24 12:44:49 by mpoplow          ###   ########.fr       */
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

int	ft_export_empty(t_list *stream, char ***copy_env)
{
	int		i;
	char	**temp;

	i = 0;
	temp = ft_strarrdup_sort(*copy_env);
	if (!temp)
		return (ft_error_cmd("Malloc failed.", "export"), 12);
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
	return(0);
}
