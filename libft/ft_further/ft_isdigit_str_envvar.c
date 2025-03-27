/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_str_plusmin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 19:30:54 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/27 19:32:41 by mpoplow          ###   ########.fr       */
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
			if ((str[i] != '-' && str[i] != '+') || i != 0 || ft_strlen(str) < 2)
				return (0);
		i++;
	}
	return (1);
}
