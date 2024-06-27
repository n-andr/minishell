/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:14:16 by lde-taey          #+#    #+#             */
/*   Updated: 2023/11/13 18:33:23 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	int	asciiyes;
	int	asciino;
	
	asciiyes = 'c';
	asciino = 547;
	printf("My result 1: %d.\n", ft_isascii(asciiyes));
	printf("My result 2: %d.\n", ft_isascii(asciino));
	printf("Library result 1: %d.\n", isascii(asciiyes));
	printf("Library result 2: %d.\n", isascii(asciino));
	return (0);
}
*/
