/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:51:09 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 11:40:06 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	unsigned char	ch;
	int				i;

	ch = c;
	i = 0;
	while (s[i] != '\0')
		i++;
	if (ch == '\0')
		return (s + i);
	while (i--)
	{
		if (s[i] == ch)
			return (s + i);
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	int	c = 't' + 256;
	char	*mystring = "This is a string";

	printf("My result is %s.\n", ft_strrchr(mystring, c));
	printf("Library result is %s.\n", strrchr(mystring, c));
	return (0);
}
*/