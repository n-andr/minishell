/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:53:04 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 11:18:35 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] != '\0' && nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return (sign * result);
}
/*
#include <stdio.h>
#include <stdlib.h>
int	main(void) 
{
    const char *str1 = "    +000012345fedsi";
    const char *str2 = "    +000012345fedsi";
	const char *str3 = "";
    const char *str4 = "";

    printf("Result of my function: %d\n", ft_atoi(str1));
    printf("Result of the library function: %d\n", atoi(str2));
	printf("Result of my function: %d\n", ft_atoi(str3));
    printf("Result of the library function: %d\n", atoi(str4));
    return (0);
}
*/