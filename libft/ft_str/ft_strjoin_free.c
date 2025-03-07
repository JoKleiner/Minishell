/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:16:42 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/07 15:54:10 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// exactly like ft_strjoin, but frees s1 before returning.
char	*ft_strjoin_free(char *s1, char const *s2)
{
	size_t	i;
	char	*dest;

	if (!s2)
		return ((char *)s1);
	if (!s1)
		return ((char *)s2);
	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		dest[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	dest[ft_strlen(s1) + i] = '\0';
	free(s1);
	return (dest);
}
