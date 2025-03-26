/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:16:25 by joklein           #+#    #+#             */
/*   Updated: 2025/03/25 18:57:13 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	creat_file(char *str, t_list *stream, bool add)
{
	int	fd;

	if (TOKEN->fd_out != STDOUT_FILENO)
		close(TOKEN->fd_out);
	if (add == true)
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_errmal("open failed");
		TOKEN->error = 1;
		return (-1);
	}
	TOKEN->fd_out = fd;
	return (0);
}

static int	file_out(char *input, int i, t_list *stream, bool add)
{
	int		i_temp;
	char	*str;

	i_temp = i;
	while (input[i] && !wh_space(input[i]) && !spec_char(input[i]))
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_until_char(i, input, input[i]);
		i++;
	}
	str = str_quote_less(&input[i_temp], i - i_temp);
	if (!str)
		return (free(input), mem_fail(stream), -1);
	if (TOKEN->out_file)
		free(TOKEN->out_file);
	TOKEN->out_file = str;
	if (creat_file(str, stream, add) == -1)
		return (free(input), -1);
	return (i);
}

int	redirect_out(char *input, int i, t_list *stream)
{
	bool	add;

	i++;
	if (input[i] == '>')
	{
		add = true;
		i++;
	}
	while (wh_space(input[i]))
		i++;
	i = file_out(input, i, stream, add);
	if (i == -1)
		return (-1);
	if (!wh_space(input[i]))
		i--;
	return (i);
}
