/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:16:25 by joklein           #+#    #+#             */
/*   Updated: 2025/03/10 16:07:02 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	creat_file(char *str, t_list *stream, bool add)
{
	int fd;

	if(TOKEN->fd_out != 1)
		close(TOKEN->fd_out);
	if(add == true)
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (free(str), -1);
	TOKEN->fd_out = fd;
	return (0);
}

int	redir_out2(char *input, int i, t_list *stream, bool add)
{
	int		num_letter;
	int		i_temp;
	char	*str;

	num_letter = 0;
	i_temp = i;
	while (!wh_space(input[i]) && !spez_char(input[i]) && input[i])
	{
		i++;
		num_letter++;
	}
	if (spez_char(input[i]))
		return (-1);
	str = ft_strndup(&input[i_temp], num_letter);
	if (!str)
		return (-1);
	TOKEN->out_file = str;
	if (creat_file(str, stream, add) == -1)
		return (-1);
	return (i);
}

int	redirect_out(char *input, int i, t_list *stream)
{
	bool add;
	i++;
	if (input[i] == '>')
	{
		add = true;
		i++;
	}
	while (wh_space(input[i]))
		i++;
	i = redir_out2(input, i, stream, add);
	if (i == -1)
		return (-1);
	return (i);
}
