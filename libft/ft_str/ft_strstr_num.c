/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:22:25 by joklein           #+#    #+#             */
/*   Updated: 2025/03/06 16:28:53 by joklein          ###   ########.fr       */
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
		while (src[i + u] == search[u])
		{
			if (search[u + 1] == '\0')
				return (u + 1 - ft_strlen(search));
			u++;
		}
		i++;
	}
	return (0);
}
