/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:05:01 by joklein           #+#    #+#             */
/*   Updated: 2025/01/22 15:24:20 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	strlen;

	strlen = 0;
	while (str[strlen] != '\0')
		strlen++;
	return (strlen);
}

char	*ft_strndup(const char *str, size_t len)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = (char *)malloc(len + 1);
	if (dst == NULL)
		return (NULL);
	while (i < len)
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

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

void	free_str(char **str)
{
	if (str && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

void	*ft_memcpy(void *dst, const void *src, size_t num)
{
	size_t		i;
	char		*dstptr;
	const char	*srcptr;

	dstptr = (char *)dst;
	srcptr = (const char *)src;
	if (dst == 0 && src == 0)
		return (NULL);
	i = 0;
	while (i < num)
	{
		dstptr[i] = srcptr[i];
		i++;
	}
	return (dst);
}
