/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:41:23 by joklein           #+#    #+#             */
/*   Updated: 2025/03/05 12:53:26 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	file_in(char *input, int i, t_list *stream)
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
	if (TOKEN->in_file)
		free(TOKEN->in_file);
	str = ft_strndup(&input[i_temp], num_letter);
	if (!str)
		return (-1);
	TOKEN->in_file = str;
	TOKEN->input = 3;
	return (i);
}

int	redirect_in(char *input, int i, t_list *stream)
{
	i++;
	if (input[i] == '<')
	{
		i++;
		while (wh_space(input[i]))
			i++;
		i = heredoc(i, input, stream);
		if (i == -1)
			return (-1);
	}
	else
	{
		while (wh_space(input[i]))
			i++;
		i = file_in(input, i, stream);
		if (i == -1)
			return (-1);
	}
	return (i);
}
