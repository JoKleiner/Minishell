/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:58:03 by joklein           #+#    #+#             */
/*   Updated: 2025/01/22 15:27:05 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	char	*dst;
	size_t	i;
	size_t	u;

	i = 0;
	u = 0;
	dst = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (dst == NULL)
		return (NULL);
	while (str1[i] != '\0')
	{
		dst[i] = str1[i];
		i++;
	}
	while (str2[u] != '\0')
	{
		dst[i] = str2[u];
		i++;
		u++;
	}
	dst[i] = '\0';
	return (dst);
}
