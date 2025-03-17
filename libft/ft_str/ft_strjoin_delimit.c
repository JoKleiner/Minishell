/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_delimit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:58:03 by joklein           #+#    #+#             */
/*   Updated: 2025/03/17 14:21:08 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin_delimit(char *str1, char middle, char *str2)
{
	char	*dst;
	size_t	i;
	size_t	u;

	i = 0;
	u = 0;
	dst = malloc(ft_strlen(str1) + ft_strlen(str2) + 2);
	if (dst == NULL)
		return (NULL);
	while (str1[i] != '\0')
	{
		dst[i] = str1[i];
		i++;
	}
	dst[i] = middle;
	i++;
	while (str2[u] != '\0')
	{
		dst[i] = str2[u];
		i++;
		u++;
	}
	dst[i] = '\0';
	return (dst);
}
