/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:57:58 by joklein           #+#    #+#             */
/*   Updated: 2025/01/22 15:27:54 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *src, const char *search, size_t len)
{
	size_t	i;
	size_t	u;

	i = 0;
	if (*search == '\0')
		return ((char *)src);
	while (src[i] != '\0' && i < len)
	{
		u = 0;
		while ((src[i + u] == search[u]) && ((i + u) < len))
		{
			if (search[u + 1] == '\0')
				return ((char *)&src[i]);
			u++;
		}
		i++;
	}
	return (0);
}
