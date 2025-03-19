/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:20:06 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/19 12:11:35 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	check_syntax(char *input)
{
	int		i;
	char	syn_char;

	i = 0;
	syn_char = '\0';
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_until_char(i, input, input[i]);
		i++;
	}
	return (syn_char);
}

// if (input[i] == '>')
// {
// 	i++;
// 	while (input[i] && wh_space(input[i]))
// 		i++;
// 	if (input[i] == '>')
// 		syn_char = input[i];
// 	return (syn_char);
// }
// if (input[i])