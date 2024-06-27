/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:55:25 by lde-taey          #+#    #+#             */
/*   Updated: 2024/04/20 15:03:55 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int i)
{
	int		counter;
	char	*newstr;

	newstr = ft_itoa(i);
	counter = ft_putstr(newstr);
	free(newstr);
	return (counter);
}
/*
#include <stdio.h>

int	main(void)
{
	int	i = -2147483648;
	int i1 = -25895;
	int i2 = 0;
	int return1;
	int return2;
	int	return3;

	return1 = ft_putnbr(i);
	printf("\nReturn value: %i\n", return1);
	return2 = ft_putnbr(i1);
	printf("\nReturn value 2: %i\n", return2);
	return3 = ft_putnbr(i2);
	printf("\nReturn value 3: %i\n", return3);
}
*/