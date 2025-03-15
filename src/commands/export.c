/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:38:19 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/14 18:37:40 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_add_envvar(char *arg, char **copy_env)
{
	char	**dest;
	int		i;
	int		len;

	len = ft_strstrlen(copy_env);
	dest = malloc(sizeof(char *) * (len + 2));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = ft_strdup(copy_env[i]);
		if (!dest[i])
			return (free_strstr(dest), NULL);
		i++;
	}
	dest[i] = ft_strdup(arg);
	if (!dest[i])
		return (free_strstr(dest), NULL);
	dest[i + 1] = NULL;
	return (dest);
}

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
	temp = ft_strstrdup_sort(*copy_env);
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
	free_strstr(temp);
}

// Executes export
void	ft_exe_export(t_list *stream, char ***copy_env)
{
	int		i;
	char	**temp;

	if (!TOKEN->arg[1])
	{
		ft_export_empty(stream, copy_env);
		return ;
	}
	i = 0;
	while (TOKEN->arg[i + 1])
	{
		temp = ft_add_envvar(TOKEN->arg[i + 1], *copy_env);
		if (!(temp))
			return (ft_error_cmd("Malloc failed.", "export"));
		free_strstr(*copy_env);
		*copy_env = temp;
		i++;
	}
}
