/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:47:56 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 12:20:31 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}
/*
#include <bsd/string.h>
#include <stdio.h>
#include <stdlib.h>
int	main(void)
{
	char	*mystring = "This is a string.";

	printf("The answer for my function is %lu.\n", ft_strlen(mystring));
	printf("The answer for the library function is %lu.\n", strlen(mystring));
	return (0);
}
*/
