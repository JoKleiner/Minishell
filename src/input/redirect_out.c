/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:16:25 by joklein           #+#    #+#             */
/*   Updated: 2025/03/03 12:58:16 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	creat_file(char *str)
{
	FILE	*file;

	file = fopen(str, "w");
	if (!file)
	{
		free(str);
		return (-1);
	}
	fclose(file);
	return(0);
}

int	redir_out2(char *input, int i, t_list *stream)
{
	int		num_letter;
	int		i_temp;
	char	*str;

	num_letter = 0;
	i_temp = i;
	while (!wh_space(input[i]) && !wr_symbol(input[i]) && input[i])
	{
		i++;
		num_letter++;
	}
	if (wr_symbol(input[i]))
		return (-1);
	str = ft_strndup(&input[i_temp], num_letter);
	if (!str)
		return (-1);
	TOKEN->out_file = str;
	TOKEN->output = 3;
	if (creat_file(str) == -1)
		return (-1);
	return (i);
}

int	redirect_out(char *input, int i, t_list *stream)
{
	i++;
	if (input[i] == '>')
	{
		TOKEN->add = 1;
		i++;
	}
	while (wh_space(input[i]))
		i++;
	i = redir_out2(input, i, stream);
	if (i == -1)
		return (-1);
	return (i);
}
