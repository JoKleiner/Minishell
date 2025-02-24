/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:02:43 by joklein           #+#    #+#             */
/*   Updated: 2025/01/22 15:26:50 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	dstlen;
	size_t	temp;
	size_t	i;

	dstlen = ft_strlen(dst);
	temp = dstlen;
	i = 0;
	if (dstlen >= len)
		return (ft_strlen(src) + len);
	while (temp + 1 < len && src[i] != '\0')
	{
		dst[temp] = src[i];
		i++;
		temp++;
	}
	dst[temp] = '\0';
	return (ft_strlen(src) + dstlen);
}
