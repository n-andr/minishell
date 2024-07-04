/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:52:23 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 11:30:17 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	unsigned char	*string1;
	unsigned char	*string2;
	size_t			i;

	string1 = (unsigned char *)s1;
	string2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (string1[i] != string2[i])
			return (*(string1 + i) - *(string2 + i));
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int main (void) 
{
	char	mystring1[] = "This is not a string";
	char	mystring2[] = "";

	printf("My result: %i.\n", ft_memcmp(mystring1, mystring2, 20));
	printf("Library result: %i.\n", memcmp(mystring1, mystring2, 20));
	return(0);
}
*/
