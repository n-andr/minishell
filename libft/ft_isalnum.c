/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:13:58 by lde-taey          #+#    #+#             */
/*   Updated: 2023/11/13 18:33:05 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	int	alnumyes;
	int	alnumno;
	
	alnumyes = '6';
	alnumno = '?';
	printf("My result 1: %d.\n", ft_isalnum(alnumyes));
	printf("My result 2: %d.\n", ft_isalnum(alnumno));
	printf("Library result 1: %d.\n", isalnum(alnumyes));
	printf("Library result 2: %d.\n", isalnum(alnumno));
	return (0);
}
*/
