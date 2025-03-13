/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:08:41 by joklein           #+#    #+#             */
/*   Updated: 2025/03/13 11:55:20 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *str, int cha)
{
	size_t	i;

	if ((unsigned char)cha == '\0')
		return ((char *)&str[ft_strlen(str)]);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)cha)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
