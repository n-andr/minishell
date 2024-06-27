/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:49:52 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 11:49:13 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	srcl;
	unsigned int	dstl;

	if (!src && !dst)
		return (0);
	srcl = ft_strlen(src);
	dstl = ft_strlen(dst);
	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && (dstl + i + 1) < size)
		{
			dst[dstl + i] = src[i];
			i++;
		}
		dst[dstl + i] = '\0';
	}
	if (dstl <= size)
		srcl = srcl + dstl;
	else
		srcl = srcl + size;
	return (srcl);
}
/*
#include <stdio.h>
#include <unistd.h>
#include <bsd/string.h>

int	main(void) 
{
	char mystring1[] = "This is a string";
	char mystring2[] = "-- and this is too";
	char mystring3[] = "This is a string";
	char mystring4[] = "-- and this is too";

	printf("My return value: %d.\n", ft_strlcat(mystring1, mystring2, 25));
	printf("My string: %s.\n", mystring1);
	printf("Library return value: %zu.\n", strlcat(mystring3, mystring4, 25));
	printf("Library string: %s.\n", mystring3);

	return(0);
}
*/
