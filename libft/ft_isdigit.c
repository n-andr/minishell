/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:13:06 by lde-taey          #+#    #+#             */
/*   Updated: 2023/11/13 18:32:50 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	int	digyes;
	int	digno;
	
	digyes = '7';
	digno = '?';
	printf("My result 1: %d.\n", ft_isdigit(digyes));
	printf("My result 2: %d.\n", ft_isdigit(digno));
	printf("Library result 1: %d.\n", isdigit(digyes));
	printf("Library result 2: %d.\n", isdigit(digno));
	return (0);
}
*/
