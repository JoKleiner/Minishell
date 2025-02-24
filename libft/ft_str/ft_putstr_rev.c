/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_rev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:33:48 by joklein           #+#    #+#             */
/*   Updated: 2025/01/22 15:27:04 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr_rev(char *str)
{
	size_t	strlen;
	int		num_ret;

	num_ret = 0;
	strlen = ft_strlen(str);
	while (strlen > 0)
	{
		if (write(1, &str[--strlen], 1) == -1)
			return (-1);
		num_ret++;
	}
	return (num_ret);
}
