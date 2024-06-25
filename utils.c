/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:02:33 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/25 22:55:19 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	args_error(void)
{
	printf("Error. This program does not accept any arguments\n");
	exit(-1);
}

void	malloc_error(void)
{
	printf("Error. Malloc failed\n");
	exit(-1);
}

char	*ft_strchr(const char *s, int c)
{
	char	*s1;
	char	ch;

	ch = (char)c;
	s1 = (char *)s;
	while (*s1 != '\0')
	{
		if (*s1 == ch)
			return (s1);
		s1++;
	}
	if (*s1 == ch)
		return (s1);
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (*s1 == '\0' && *s2 == '\0')
		return (0);
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}


size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

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