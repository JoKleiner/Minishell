/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_str_envvar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 10:56:10 by joklein           #+#    #+#             */
/*   Updated: 2025/03/28 10:56:15 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isdigit_str_plusmin(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (0 == ft_isdigit(str[i]))
			if ((str[i] != '-' && str[i] != '+') || i != 0
				|| ft_strlen(str) < 2)
				return (0);
		i++;
	}
	return (1);
}
