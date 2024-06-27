/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:33:25 by lde-taey          #+#    #+#             */
/*   Updated: 2023/11/26 19:33:27 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	getlength(int n)
{
	size_t		digits;
	long int	longn;

	longn = n;
	digits = 1;
	if (longn < 0)
	{
		digits++;
		longn = longn * -1;
	}
	while (longn >= 10)
	{
		longn = longn / 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char		*string;
	size_t		len;
	long int	longn;

	longn = n;
	len = getlength(longn);
	string = (char *)malloc((len + 1) * sizeof(char));
	if (string == 0)
		return (0);
	string[len] = '\0';
	if (longn < 0)
	{
		longn = longn * -1;
		string[0] = '-';
	}
	if (longn == 0)
		string[0] = '0';
	while (longn >= 1)
	{
		len--;
		string[len] = (longn % 10) + '0';
		longn = longn / 10;
	}
	return (string);
}
/*
#include <stdio.h>

int	main(void)
{
	int	number = -2147483648LL;

	printf("My result: %s.\n", ft_itoa(number));
}
*/