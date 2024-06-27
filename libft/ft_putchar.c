/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:51:32 by lde-taey          #+#    #+#             */
/*   Updated: 2024/04/20 15:03:06 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
/*
#include <stdio.h>

int	main(void)
{
	char c = '5';
	int returnv;

	returnv = ft_putchar(c);
	printf("\nReturn value: %i", returnv);
	return (0);
}
*/