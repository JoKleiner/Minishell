/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joklein <joklein@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:50:25 by joklein           #+#    #+#             */
/*   Updated: 2025/01/22 16:13:54 by joklein          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	percent_found(va_list arg_list, char cha)
{
	int	num_ret;

	num_ret = 0;
	if (cha == 'c')
		num_ret = ft_putchar((char)va_arg(arg_list, int));
	if (cha == 's')
		num_ret = ft_putstr((char *)va_arg(arg_list, char *));
	if (cha == 'd' || cha == 'i')
		num_ret = ft_putnbr((int)va_arg(arg_list, int));
	if (cha == 'p')
		num_ret = case_p((size_t)va_arg(arg_list, size_t));
	if (cha == 'u')
		num_ret = case_u(va_arg(arg_list, unsigned int));
	if (cha == 'x' || cha == 'X')
		num_ret = case_xx(va_arg(arg_list, unsigned int), cha);
	if (cha == '%')
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		num_ret++;
	}
	return (num_ret);
}

int	ft_printf(const char *arg, ...)
{
	long	i;
	int		num_check;
	int		num_ret;
	va_list	arg_list;

	va_start(arg_list, arg);
	i = -1;
	num_ret = 0;
	while (arg[++i] != '\0')
	{
		if (arg[i] == '%')
		{
			num_check = percent_found(arg_list, arg[++i]);
			if (num_check == -1)
				return (-1);
			num_ret += num_check;
		}
		else
		{
			if (write(1, &arg[i], 1) == -1)
				return (-1);
			num_ret++;
		}
	}
	return (va_end(arg_list), num_ret);
}
