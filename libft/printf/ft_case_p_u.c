/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_p_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:38:29 by joklein           #+#    #+#             */
/*   Updated: 2025/01/22 16:13:43 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	case_p(size_t num)
{
	int		num_ret;
	int		temp;
	char	buffer[17];
	size_t	u;

	u = 0;
	num_ret = ft_putstr("0x");
	if (num_ret == -1)
		return (-1);
	if (num == 0)
		buffer[u++] = '0';
	else
	{
		while (num != 0)
		{
			buffer[u++] = HEX_LOW[num % 16];
			num = num / 16;
		}
	}
	buffer[u] = '\0';
	temp = ft_putstr_rev(buffer);
	if (temp == -1)
		return (-1);
	num_ret = num_ret + temp;
	return (num_ret);
}

int	case_u(unsigned int numunsign)
{
	int	num_ret;

	num_ret = 0;
	if (numunsign >= 10)
		num_ret = case_u(numunsign / 10);
	if (num_ret == -1)
		return (-1);
	if (ft_putchar(numunsign % 10 + '0') == -1)
		return (-1);
	return (num_ret + 1);
}
