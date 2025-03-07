/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:16:42 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/07 12:31:36 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// exactly like ft_strjoin, but frees s1 before returning.
char	*ft_strjoin_free(char *s1, char const *s2)
{
	size_t	i;
	size_t	s1len;
	char	*dest;

	s1len = ft_strlen(s1);
	dest = malloc(s1len + ft_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	if (!s1)
		return ((char *)s2);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		dest[s1len + i] = s2[i];
		i++;
	}
	dest[s1len + i] = '\0';
	free(s1);
	return (dest);
}
