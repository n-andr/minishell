/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:52:42 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 11:27:00 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *big, char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return (big);
	j = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return (big + i);
			j++;
		}
		i++;
	}
	return (0);
}
/*
#include <bsd/string.h>
#include <stdio.h>
int main(void)
{
	char	*smallstring = "dolor";
	char	*bigstring = "lorem ipsum dolor sit amet";

	printf("My result: %s.\n", ft_strnstr(bigstring, smallstring, 15));
	printf("Library result: %s.\n", strnstr(bigstring, smallstring, 15));
	return (0);
}
*/