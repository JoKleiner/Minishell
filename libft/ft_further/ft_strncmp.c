/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:40:31 by joklein           #+#    #+#             */
/*   Updated: 2025/03/05 11:55:23 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *src1, const char *src2, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num && src1[i] && src2[i])
	{
		if (src1[i] != src2[i])
			return ((unsigned char)src1[i] - (unsigned char)src2[i]);
		i++;
	}
	if (i == num)
		return (0);
	if(src2[i])
		return(0-(unsigned char)src2[i]);
	return ((unsigned char)src1[i]-0);
}
