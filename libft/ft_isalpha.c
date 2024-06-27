/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:50:02 by lde-taey          #+#    #+#             */
/*   Updated: 2023/11/13 18:32:36 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	int	charyes;
	int	charno;
	
	charyes = 'a';
	charno = '?';
	printf("My result 1: %d.\n", ft_isalpha(charyes));
	printf("My result 2: %d.\n", ft_isalpha(charno));
	printf("Library result 1: %d.\n", isalpha(charyes));
	printf("Library result 2: %d.\n", isalpha(charno));
	return (0);
}
*/
