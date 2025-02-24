/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:37:41 by joklein           #+#    #+#             */
/*   Updated: 2025/01/22 15:27:05 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *str)
{
	char	*dst;
	size_t	i;
	size_t	u;

	i = 0;
	u = 0;
	while (str[i] != '\0')
		i++;
	dst = (char *) malloc(i + 1);
	if (dst == NULL)
		return (NULL);
	while (u < i)
	{
		dst[u] = str[u];
		u++;
	}
	dst[u] = '\0';
	return (dst);
}
