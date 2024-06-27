/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:01:29 by lde-taey          #+#    #+#             */
/*   Updated: 2024/04/20 15:04:07 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	getlength(unsigned long decp)
{
	size_t			counter;
	unsigned long	ptr;

	counter = 0;
	ptr = decp;
	while (ptr > 0)
	{
		ptr = ptr / 16;
		counter++;
	}
	return (counter);
}

int	ft_putptr(void *ptr)
{
	int				len;
	int				returnv;
	unsigned long	decp;
	char			*newstr;
	char			*base;

	if (!ptr)
		return (ft_putstr("(nil)"));
	ft_putstr("0x");
	decp = (unsigned long)ptr;
	len = getlength(decp);
	newstr = (char *)malloc((len + 1) * sizeof(char));
	if (!newstr)
		return (0);
	base = "0123456789abcdef";
	newstr [len] = '\0';
	while (decp >= 1)
	{
		len--;
		newstr[len] = base[decp % 16];
		decp /= 16;
	}
	returnv = ft_putstr(newstr);
	free (newstr);
	return (returnv + 2);
}
/*
#include <stdio.h>

int	main(void)
{
	char *str = "This is a string";
	void *ptr = &str;
	void *ptr2 = NULL;
	int returnv;
	int returnv2;

	returnv = ft_putptr(ptr);
	printf("\nReturn value: %i\n", returnv);
	returnv2 = ft_putptr(ptr2);
	printf("\nReturn value: %i\n", returnv2);
	return (0);
}
*/