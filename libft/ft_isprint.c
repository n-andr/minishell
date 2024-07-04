/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:14:35 by lde-taey          #+#    #+#             */
/*   Updated: 2023/11/13 18:33:38 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	int	printyes;
	int	printno;
	
	printyes = 40;
	printno = 2;
	printf("My result 1: %d.\n", ft_isprint(printyes));
	printf("My result 2: %d.\n", ft_isprint(printno));
	printf("Library result 1: %d.\n", isprint(printyes));
	printf("Library result 2: %d.\n", isprint(printno));
	return (0);
}
*/
