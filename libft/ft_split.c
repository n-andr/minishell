/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:33:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/05 15:39:20 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_make_words(char const *s, char c, size_t wordcount, char **words)
{
	char	*nextword;

	while (*s && *s == c)
		s++;
	while (wordcount--)
	{
		nextword = ft_strchr(s, c);
		if (nextword != 0)
		{
			*words = ft_substr(s, 0, (nextword - s));
			while (*nextword && *nextword == c)
				nextword++;
			s = nextword;
		}
		else
			*words = ft_substr(s, 0, (ft_strlen(s) + 1));
		words++;
	}
	*words = 0;
}

static size_t	ft_wordcount(char const *s, char c)
{
	int			i;
	size_t		wordcount;
	int			skip;

	i = 0;
	skip = 1;
	wordcount = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && skip == 1)
		{
			skip = 0;
			wordcount++;
		}
		else if (s[i] == c)
			skip = 1;
		i++;
	}
	return (wordcount);
}

char	**ft_split(char const *s, char c)
{
	size_t	wordcount;
	char	**words;

	if (s == 0)
		return (0);
	wordcount = ft_wordcount(s, c);
	words = (char **)malloc((wordcount + 1) * sizeof(char *));
	if (words == 0)
		return (0);
	ft_make_words(s, c, wordcount, words);
	return (words);
}

// #include <stdio.h>

// int	main(void)
// {
// 	// char *mystring = "    Lieselot De Taeye ";
// 	char **strings;
// 	int	i;

// 	strings = ft_split("\t\t\t\thello!\t\t\t\t", '\t');
// 	i = 0;
// 	while (strings[i] != 0)
// 	{
// 		printf("This is one of the words: %s.\n", strings[i]);
// 		free (strings[i]);
// 		i++;
// 	}
// 	free (strings);
// 	return (0);
// }
