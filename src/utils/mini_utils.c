/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:12:43 by joklein           #+#    #+#             */
/*   Updated: 2025/03/19 15:13:06 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
