/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:02:33 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/20 16:54:38 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
		length++;
	return (length);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptr_d;
	char		*ptr_s;
	size_t		i;

	ptr_d = (char *)dest;
	ptr_s = (char *)src;
	if (!ptr_d && !ptr_s)
		return (0);
	i = 0;
	while (i < n)
	{
		*ptr_d = *ptr_s;
		ptr_d++;
		ptr_s++;
		i++;
	}
	return (dest);
}

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

int	ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (*(s1 + i) && *(s1 + i) == *(s2 + i))
		i++;
	return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return (0);
}