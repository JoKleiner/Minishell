/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:41:23 by joklein           #+#    #+#             */
/*   Updated: 2025/03/24 10:06:26 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	file_in(char *input, int i, t_list *stream)
{
	int		i_temp;
	char	*str;
	int		fd;

	i_temp = i;
	while (input[i] && !wh_space(input[i]) && !spec_char(input[i]))
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_until_char(i, input, input[i]);
		i++;
	}
	str = str_quote_less(&input[i_temp], i - i_temp);
	if (!str)
		return (mem_fail(stream), -1);
	if (TOKEN->in_file)
		free(TOKEN->in_file);
	TOKEN->in_file = str;
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		ft_error_cmd(": No such file or directory", str);
		return (TOKEN->error = errno, -1);
	}
	close(fd);
	TOKEN->fd_in = -3;
	return (i);
}

int	redirect_in(char *input, int i, t_list *stream, char **copy_env)
{
	i++;
	if (input[i] == '<')
	{
		i++;
		while (wh_space(input[i]))
			i++;
		i = heredoc(i, input, stream, copy_env);
	}
	else
	{
		while (wh_space(input[i]))
			i++;
		i = file_in(input, i, stream);
	}
	if (i == -1)
		return (free(input), -1);
	if (input[i] == '\0')
		i--;
	return (i);
}
