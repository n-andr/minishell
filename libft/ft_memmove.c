/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:48:58 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 12:11:36 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_d;
	unsigned char	*temp;
	size_t			i;

	if (!dest && !src)
		return (0);
	ptr_d = (unsigned char *)dest;
	temp = (unsigned char *)src;
	i = 0;
	if (temp > ptr_d)
	{
		while (i < n)
		{
			ptr_d[i] = temp[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i--)
			ptr_d[i] = temp[i];
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	main(void) 
{
	char	mystring1[] = "This is not a string.";
	char	mystring2[] = "This is a string.";
	char	mystring3[] = "This is not a string.";
	char	mystring4[] = "This is a string.";
	char	mystring5[] = "This is a string";
	char	mystring6[] = "This is a string";

	ft_memmove(mystring1, mystring2, 10);
	printf("My result: %s.\n", mystring1);
	memmove(mystring3, mystring4, 10);
	printf("Library result: %s.\n", mystring3);
	ft_memmove(mystring5 + 10, mystring5, 5);
	printf("My result: %s.\n", mystring5);
	memmove(mystring6 + 10, mystring6, 5);
	printf("Library result: %s.\n", mystring6);

	return(0);
}
*/