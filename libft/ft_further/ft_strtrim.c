/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:20:17 by joklein           #+#    #+#             */
/*   Updated: 2025/01/22 15:28:03 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_trim1(char const *str, char const *set)
{
	size_t	u;
	size_t	trim1;

	trim1 = 0;
	u = 0;
	while (str[trim1] != '\0' && set[u] != '\0')
	{
		u = 0;
		while (str[trim1] != set[u] && set[u] != '\0')
			u++;
		if (str[trim1] == set[u])
		{
			trim1++;
			continue ;
		}
		break ;
	}
	return (trim1);
}

size_t	ft_trim2(char const *str, char const *set, size_t trim1)
{
	size_t	u;
	size_t	trim2;

	trim2 = ft_strlen(str) - 1;
	u = 0;
	while (set[u] != '\0' && trim2 > trim1)
	{
		u = 0;
		while (str[trim2] != set[u] && set[u] != '\0')
			u++;
		if (str[trim2] == set[u])
		{
			trim2--;
			continue ;
		}
	}
	return (trim2);
}

char	*ft_strtrim(char const *str, char const *set)
{
	char	*dst;
	size_t	trim1;
	size_t	trim2;
	size_t	dstlen;

	if (str == NULL || set == NULL)
		return (NULL);
	if (str[0] == '\0')
	{
		dst = (char *)malloc(1);
		if (dst == NULL)
			return (NULL);
		dst[0] = '\0';
		return (dst);
	}
	trim1 = ft_trim1(str, set);
	trim2 = ft_trim2(str, set, trim1);
	dstlen = trim2 - trim1 + 1;
	dst = (char *)malloc(dstlen + 1);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, &str[trim1], dstlen + 1);
	return (dst);
}
