/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:36:18 by joklein           #+#    #+#             */
/*   Updated: 2025/01/22 15:40:58 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr(int num)
{
	char	str[12];
	long	numlong;
	int		i;
	long	temp;

	numlong = num;
	i = 0;
	if (num == 0)
		return (write(1, "0", 1));
	if (numlong < 0)
	{
		str[i++] = '-';
		numlong = -numlong;
	}
	temp = numlong;
	while (temp > 0 && i++ >= 0)
		temp = temp / 10;
	str[i] = '\0';
	while (numlong > 0)
	{
		str[--i] = (numlong % 10) + '0';
		numlong = numlong / 10;
	}
	return (write(1, str, ft_strlen(str)));
}
