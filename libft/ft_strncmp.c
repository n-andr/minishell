/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:51:37 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 11:36:40 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <unistd.h>
#include <bsd/string.h>

int main (void) 
{
    char mystring1[] = "test";
    char mystring2[] = "testss";
    char mystring3[] = "test";
    char mystring4[] = "testss";

    printf("My result: %d.\n", ft_strncmp(mystring1, mystring2, 7));
    printf("Library result: %d.\n", strncmp(mystring3, mystring4, 7));
    return(0);
}
*/