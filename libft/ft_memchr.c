/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:52:01 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 11:34:12 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;
	unsigned char	ch;
	size_t			i;

	string = (unsigned char *)s;
	ch = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (string[i] == ch)
			return ((void *)s + i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void) 
{
	char	mystring1[] = "This is a string";
	char	mystring2[] = "This is a string";
	int	c = 'i';

	printf("My result; %p.\n", ft_memchr(mystring1, c, 10));
	printf("Library result: %p.\n", memchr(mystring2, c, 10));

	return(0);
}
*/
