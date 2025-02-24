/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:43:25 by joklein           #+#    #+#             */
/*   Updated: 2025/01/22 15:26:45 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	mem_fill(char **ptr, long num, int i)
{
	(*ptr) = (char *)malloc(i + 1);
	if (*ptr == NULL)
		return (0);
	(*ptr)[i] = '\0';
	(*ptr)[0] = '-';
	while (num > 0)
	{
		(*ptr)[i - 1] = (num % 10) + '0';
		num = num / 10;
		i--;
	}
	return (1);
}

char	*ft_itoa(int num)
{
	char	*ptr;
	int		i;
	long	temp;
	long	lng_num;

	ptr = NULL;
	lng_num = num;
	if (lng_num == 0)
		return (ft_strdup("0"));
	i = 0;
	if (lng_num < 0)
	{
		i++;
		lng_num = -lng_num;
	}
	temp = lng_num;
	while (temp > 0)
	{
		temp = temp / 10;
		i++;
	}
	if (mem_fill(&ptr, lng_num, i) == 0)
		return (NULL);
	return (ptr);
}
