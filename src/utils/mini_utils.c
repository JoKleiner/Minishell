/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:12:43 by joklein           #+#    #+#             */
/*   Updated: 2025/04/01 19:06:47 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	am_rd(char *str_temp)
{
	printf("%s: ambiguous redirect\n", str_temp);
}

int	wh_space(char input)
{
	if (input == ' ' || input == '\t' || input == '\n')
		return (1);
	return (0);
}

int	spec_char(char input)
{
	if (input == '<' || input == '>')
		return (1);
	if (input == '|')
		return (1);
	return (0);
}

char	*creat_env_str(int i, int i_temp, char *input)
{
	char	*str;

	str = ft_strndup(&input[i_temp + 1], i - i_temp);
	if (!str)
		return (NULL);
	str = ft_strjoin_free(str, "=");
	if (!str)
		return (NULL);
	return (str);
}

int	redir_char(char input)
{
	if (input == '<' || input == '>')
		return (1);
	if (input == '|' || input == '&')
		return (1);
	return (0);
}
