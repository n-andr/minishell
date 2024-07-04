/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:50:48 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 12:39:58 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	ch;

	i = 0;
	ch = c;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return ((char *)s + i);
		i++;
	}
	if (ch == '\0')
		return ((char *)s + i);
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	int	c = 'i';
	char	*mystring = "This is a string";

	printf("The answer for my function is %s.\n", ft_strchr(mystring, c));
	printf("The answer for the library function is %s.\n", strchr(mystring, c));
	return (0);
}
*/
