/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:16:25 by joklein           #+#    #+#             */
/*   Updated: 2025/03/12 15:06:52 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	creat_file(char *str, t_list *stream, bool add)
{
	int	fd;

	if (TOKEN->fd_out != STDOUT_FILENO)
		close(TOKEN->fd_out);
	if (add == true)
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
	if (fd == -1)
		return (free(str), -1);
	TOKEN->fd_out = fd;
	return (0);
}

char	*str_quote_less(char *input, int len)
{
	char	*dst;
	int		i;
	int		u;

	i = 0;
	u = 0;
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	while (i < len)
	{
		if (input[i] == '\"' || input[i] == '\'')
			i++;
		else
		{
			dst[u] = input[i];
			i++;
			u++;
		}
	}
	dst[u] = '\0';
	return (dst);
}

int	file_out(char *input, int i, t_list *stream, bool add)
{
	int		i_temp;
	char	*str;

	i_temp = i;
	while (input[i] && !wh_space(input[i]) && !spec_char_wo_dol(input[i]))
	{
		if (input[i] == '\'')
			i = skip_until_char(i, input, '\'');
		if (input[i] == '\"')
			i = skip_until_char(i, input, '\"');
		i++;
	}
	str = str_quote_less(&input[i_temp], i - i_temp);
	if (!str)
		return (-1);
	if (TOKEN->out_file)
		free(TOKEN->out_file);
	TOKEN->out_file = str;
	if (creat_file(str, stream, add) == -1)
		return (-1);
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
	return (i);
}
