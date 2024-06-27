/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:45:44 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 12:22:59 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*string;
	size_t			i;

	string = s;
	i = 0;
	while (i < n)
	{
		string[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void) 
{
	char	mystring1[] = "This is a string";
	char	mystring2[] = "This is a string";

	ft_memset(mystring1, '0', 10);
	memset(mystring2, '0', 10);
	printf("The result for my function is %s.\n", mystring1);
	printf("The result for the library function is %s.\n", mystring2);

	return(0);
}
*/
