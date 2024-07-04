/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:48:18 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 12:18:56 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*string;
	size_t			i;

	string = s;
	i = 0;
	while (i < n)
	{
		string[i] = '\0';
		i++;
	}
}
/*
#include <stdio.h>
#include <string.h>

int	main (void) 
{
	char	mystring1[] = "This is a string.";
	char	mystring2[] = "This is a string.";
	char	mystring3[] = "";
	char	mystring4[] = "";

	ft_bzero(mystring1, 4);
	bzero(mystring2, 4);
	ft_bzero(mystring3, 10);
	bzero(mystring4, 10);
	printf("The result for my function is %s.\n", mystring1);
	printf("The result for the library function is %s.\n", mystring2);
	printf("The result for my function is %s.\n", mystring3);
	printf("The result for the library function is %s.\n", mystring4);

	return(0);
}
*/
