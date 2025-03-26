/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:33:48 by joklein           #+#    #+#             */
/*   Updated: 2025/03/25 15:55:44 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long	ft_putstr_fd(char *str, int fd)
{
	size_t	strlen;

	if (str == NULL)
	{
		if (write(fd, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	strlen = ft_strlen((const char *)str);
	if (write(fd, str, strlen) == -1)
		return (-1);
	return (strlen);
}
