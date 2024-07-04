/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:45:00 by lde-taey          #+#    #+#             */
/*   Updated: 2024/04/20 15:04:18 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int	i;
	int	i2;

	i = 0;
	if (!str)
	{
		i2 = ft_putstr("(null)");
		return (i2);
	}
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}
/*
#include <stdio.h>

int	main(void)
{
	char *str = "This is a string";
	char *str2 = NULL;
	int returnv;
	int returnv2;

	returnv = ft_putstr(str);
	printf("\nReturn value: %i\n", returnv);
	returnv2 = ft_putstr(str2);
	printf("\nReturn value: %i\n", returnv2);
	return (0);
}
*/