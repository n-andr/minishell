/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:29:53 by lde-taey          #+#    #+#             */
/*   Updated: 2024/04/20 15:06:16 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_scan(char sign, va_list list)
{
	if (sign == 'c')
		return (ft_putchar(va_arg(list, int)));
	else if (sign == 's')
		return (ft_putstr(va_arg(list, char *)));
	else if (sign == 'p')
		return (ft_putptr(va_arg(list, void *)));
	else if (sign == 'd' || sign == 'i')
		return (ft_putnbr(va_arg(list, int)));
	else if (sign == 'u')
		return (ft_putuni(va_arg(list, unsigned int)));
	else if (sign == 'x')
		return (ft_puthexax(va_arg(list, unsigned int)));
	else if (sign == 'X')
		return (ft_puthexaxl(va_arg(list, unsigned int)));
	else if (sign == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *ipstring, ...)
{
	va_list	list;
	int		counter;
	int		i;

	va_start(list, ipstring);
	counter = 0;
	i = 0;
	if (!ipstring)
		return (-1);
	while (ipstring[i] != '\0')
	{
		if (ipstring[i] == '%')
		{
			counter += ft_scan(ipstring[i + 1], list);
			i++;
		}
		else
			counter += ft_putchar(ipstring[i]);
		i++;
	}
	va_end(list);
	return (counter);
}
