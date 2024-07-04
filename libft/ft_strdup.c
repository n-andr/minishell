/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:54:19 by lde-taey          #+#    #+#             */
/*   Updated: 2023/12/01 11:20:36 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*newstr;
	size_t	length;

	length = ft_strlen(s) + 1;
	newstr = (char *)malloc(length * sizeof(char));
	if (newstr == 0)
		return (0);
	ft_memcpy(newstr, s, length);
	return (newstr);
}
/*
int main(void)
{
    char *mystring = "This is a string";
    
    void *ptr = ft_strdup(mystring);
    free(ptr);
    return (0);
}
*/
