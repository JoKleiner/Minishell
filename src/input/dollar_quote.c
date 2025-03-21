/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 08:53:40 by joklein           #+#    #+#             */
/*   Updated: 2025/03/20 12:04:18 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	double_quote(int i, char **input, char **copy_env, t_list *stream)
{
	int	i_temp;

	i++;
	while ((*input)[i] && (*input)[i] != '\"')
	{
		if ((*input)[i] == '$')
		{
			i_temp = i;
			while ((*input)[i_temp] != '\"')
				i_temp--;
			if (if_heredoc(i_temp, *input))
			{
				i++;
				continue ;
			}
			*input = dollar_found(i, *input, copy_env, stream);
			if (!(*input))
				return (-1);
			i++;
		}
		i++;
	}
	if ((*input)[i] == '\0')
		i--;
	return (i);
}

int	found_quote(int i, char **input, char **copy_env, t_list *stream)
{
	if ((*input)[i] == '\'')
		i = skip_until_char(i, *input, '\'');
	if ((*input)[i] == '\"')
		i = double_quote(i, input, copy_env, stream);
	return (i);
}
