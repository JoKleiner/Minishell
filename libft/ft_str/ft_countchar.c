/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:30:46 by mpoplow           #+#    #+#             */
/*   Updated: 2025/03/24 16:32:55 by mpoplow          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int ft_countchar(char *str, char c)
{
	int i;
	int num;

	i = 0;
	num = 0;
	while(str[i])
	{
		if(str[i] == c)
			num++;
		i++;
	}
	return(num);
}
