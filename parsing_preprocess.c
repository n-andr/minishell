/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_preprocess.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:00:10 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/17 00:23:12 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	preprosess_quotes(char *input, int i, char quote)
{
	while (input[i] != quote && input[i] != '\0')
	{
		if (input[i] == ' ')
			input[i] = '\1';
		i++;
	}
	return (i);
}

static char	*insert_spaces(char *input, int i, int len)
{
	char	*new_input;
	int		j;
	int		k;

	j = 0;
	k = 0;
	new_input = malloc((ft_strlen(input) + 3) * sizeof(char));
	if (!new_input)
		return (NULL);
	while (input[j] != '\0')
	{
		if (j == i)
		{
			new_input[k++] = ' ';
			while (len-- > 0)
				new_input[k++] = input[j++];
			new_input[k++] = ' ';
		}
		else
			new_input[k++] = input[j++];
	}
	new_input[k] = '\0';
	free(input);
	return (new_input);
}

bool	next_pipe(char *input, int i)
{
	if (input[i] == '|')
	{
		return (true);
	}
	while (input[i] != '\0')
	{
		if (input[i] == '|')
			return (true);
		else if (input[i] != ' ' && input[i] != '|')
			return (false);
		i++;
	}
	return (false);
}

static int	preprosess_pipe_redir(char **input, int i)
{
	if ((*input)[i] == '|')
	{
		if (next_pipe((*input), i + 1))
			return (pipe_error());
		else
		{
			(*input) = insert_spaces((*input), i, 1);
			i += 2;
		}
	}
	else if ((*input)[i] == '<' || (*input)[i] == '>')
	{
		if ((*input)[i + 1] == (*input)[i])
		{
			(*input) = insert_spaces((*input), i, 2);
			i += 3;
		}
		else
		{
			(*input) = insert_spaces((*input), i, 1);
			i += 2;
		}
	}
	return (i);
}

int	preprosess_string(char **input)
{
	int	i;

	i = 0;
	while ((*input)[i] != '\0')
	{
		if ((*input)[i] == '\'' || (*input)[i] == '\"')
			i = preprosess_quotes((*input), i + 1, (*input)[i]);
		if ((*input)[i] == '\0')
		{
			unclosed_quote();
			return (-1);
		}
		if ((*input)[i] == '|' || (*input)[i] == '<' || (*input)[i] == '>')
		{
			i = preprosess_pipe_redir(input, i);
			if (i == -1)
				return (-1);
		}
		if ((*input)[i] == 9)
			(*input)[i] = ' ';
		i ++;
	}
	return (0);
}
