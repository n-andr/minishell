/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:33:39 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/04 16:36:51 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*newstring;
	size_t	len;
	int		i;

	len = ft_strlen(s);
	newstring = (char *)malloc((len + 1) * sizeof(char));
	if (newstring == 0)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		newstring[i] = f(i, s[i]);
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
/*
char	ft_numericmapping(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (c - 32);
	return (c);
}

#include <stdio.h>

int	main(void)
{
	char	*mystring = "exampleofastring";
	char	*resultstring;
	resultstring = ft_strmapi(mystring, ft_numericmapping);
	printf("Resulting string: %s\n", resultstring);
	free(resultstring);
	return (0);
}
*/