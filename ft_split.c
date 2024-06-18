/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:49:10 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/18 17:41:15 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	count_words(char const *s, char c)
{
	int	words;

	words = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		while (*s != c && *s != '\0')
			s++;
		words++;
	}
	return (words);
}

static char	*find_next_word(char **s_pointer, char c)
{
	char	*start;
	size_t	len;
	char	*word;
	char	*s;

	s = *s_pointer;
	while (*s == c)
		s++;
	start = (char *)s;
	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	word = (char *)malloc(len + 1);
	if (word == 0)
	{
		return (NULL);
	}
	ft_strlcpy(word, start, len + 1);
	*s_pointer = s;
	return (word);
}

static void	split_words(char *result[], char const *s, char c, int words)
{
	int		current_word;
	char	*word;
	char	*sdub;

	sdub = (char *)s;
	current_word = 0;
	while (current_word < words)
	{
		word = find_next_word(&sdub, c);
		if (word == NULL)
		{
			result = NULL;
			return ;
		}
		result[current_word] = word;
		current_word++;
	}
	result[current_word] = NULL;
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**result;

	words = count_words(s, c);
	result = malloc((words + 1) * sizeof(char *));
	if (result == 0)
		return (NULL);
	split_words(result, s, c, words);
	return (result);
}
/*#include <stdio.h>

int main() {
	char const *input_string = "split    me pls";
	char delimiter = ' ';

	printf("Original String: %s\n", input_string);
	printf("Delimiter: %c\n", delimiter);

	char **result = ft_split(input_string, delimiter);

	if (result) {
		printf("\nSplit Result:\n");
		char **temp = result; // Fix: Create a temporary pointer
		while (*temp)
		{
			printf("%s\n", *temp);
			temp++;
		}
		free(result);
	} else {
		printf("\nError: Memory allocation failed or input string is empty.\n");
	}

	return 0;
}*/