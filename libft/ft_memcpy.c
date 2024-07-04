/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:48:44 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 12:16:13 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptr_d;
	char		*ptr_s;
	size_t		i;

	ptr_d = (char *)dest;
	ptr_s = (char *)src;
	if (!ptr_d && !ptr_s)
		return (0);
	i = 0;
	while (i < n)
	{
		*ptr_d = *ptr_s;
		ptr_d++;
		ptr_s++;
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	main (void) 
{
	char mystring1[] = "This is not a string.";
	char mystring2[] = "This is a string.";
	char mystring3[] = "This is not a string.";
	char mystring4[] = "This is a string.";
	char mystring5[] = "";
	char mystring6[] = "";


	ft_memcpy(mystring1, mystring2, 10);
	printf("The result for my function is %s.\n", mystring1);
	memcpy(mystring3, mystring4, 10);
	printf("The result for the library function is %s.\n", mystring3);
	ft_memcpy(mystring5, mystring6, 10);
	printf("Result2 for my function is %s.\n", mystring5);

	return (0);
}
*/
