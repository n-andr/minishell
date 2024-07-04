/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexaxl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:17:14 by lde-taey          #+#    #+#             */
/*   Updated: 2024/04/20 15:03:32 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	getlength(unsigned long ln)
{
	size_t			counter;
	unsigned long	lncp;

	counter = 0;
	lncp = ln;
	if (lncp == 0)
		counter = 1;
	while (lncp > 0)
	{
		lncp = lncp / 16;
		counter++;
	}
	return (counter);
}

int	ft_puthexaxl(unsigned int i)
{
	int				len;
	int				returnv;
	unsigned long	ln;
	char			*newstr;
	char			*base;

	ln = i;
	len = getlength(ln);
	newstr = (char *)malloc((len + 1) * sizeof(char));
	if (!newstr)
		return (0);
	base = "0123456789ABCDEF";
	newstr [len] = '\0';
	if (ln == 0)
		newstr [0] = '0';
	while (ln >= 1)
	{
		len--;
		newstr[len] = base[ln % 16];
		ln /= 16;
	}
	returnv = ft_putstr(newstr);
	free (newstr);
	return (returnv);
}
/*
#include <stdio.h>

int	main(void)
{
	unsigned int i = 2147483647;
	unsigned int i2 = 0;
	unsigned int i3 = 458732;
	int returnv;
	int returnv2;
	int returnv3;

	returnv = ft_puthexaX(i);
	printf("\nReturn value: %i\n", returnv);
	returnv2 = ft_puthexaX(i2);
	printf("\nReturn value: %i\n", returnv2);
	returnv3 = ft_puthexaX(i3);
	printf("\nReturn value: %i\n", returnv3);
	return (0);
}
*/