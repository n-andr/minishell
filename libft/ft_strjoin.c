/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:32:37 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 11:16:11 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	s1len;
	unsigned int	totlen;
	char			*newstr;

	s1len = ft_strlen(s1) + 1;
	totlen = s1len + ft_strlen(s2);
	newstr = (char *) malloc(totlen * sizeof(char));
	if (newstr == 0)
		return (0);
	ft_strlcpy(newstr, s1, s1len);
	ft_strlcat(newstr, s2, totlen);
	return (newstr);
}
/*
#include <stdio.h>

int main(void)
{
    char mystring1[] = "This is a string ";
    char mystring2[] = "-- and this is too";
	char *result = ft_strjoin(mystring1, mystring2);

    printf("Result of my function: %s", result);
	free (result);
	return (0);
}
*/
