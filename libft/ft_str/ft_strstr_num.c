/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:22:25 by joklein           #+#    #+#             */
/*   Updated: 2025/03/28 10:06:29 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strstr_num(const char *src, const char *search)
{
	size_t	i;
	size_t	u;

	i = 0;
	if (*search == '\0')
		return (0);
	while (src[i] != '\0')
	{
		u = 0;
		while (src[i + u] && search[u] && src[i + u] == search[u])
			u++;
		if (search[u] == '\0')
			return (i);
		i++;
	}
	if (search[u] == '\0')
		return (i);
	return (0);
}
