/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:49:25 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 11:52:51 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	srcl;

	srcl = ft_strlen(src);
	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i + 1 < size)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcl);
}
/*
#include <stdio.h>
#include <unistd.h>
#include <bsd/string.h>

int	main(void) 
{
	char	mystring1[] = "";
	char	mystring2[] = "This is not a string.";
	char	mystring3[] = "";
	char	mystring4[] = "This is not a string.";

	ft_strlcpy(mystring1, mystring2, 0);
	printf("My result: %s.\n", mystring1);
	strlcpy(mystring3, mystring4, 0);
	printf("Library result: %s.\n", mystring3);

	return(0);
}
*/
