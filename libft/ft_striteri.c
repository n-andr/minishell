/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:34:02 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/04 18:29:09 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
}
/*
Tests don't work

void	*ft_toupperifeven(unsigned int i, char *string)
{
	if (i % 2 == 0)
		return (string + (i * 2));
	return (string);
}

#include <stdio.h>

int	main(void)
{
	char	*mystring = "exampleofastring";
	ft_striteri(mystring, ft_toupperifeven);
	printf("Resulting string: %s\n", mystring);
	return (0);
}
*/