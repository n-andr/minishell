/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:00:10 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/25 21:26:08 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// wee need strings for execve(), so i have desided to go for 2-d array


static int	preprosess_quotes(char *input, int i, char quote)
{
	while (input[i] != quote && input[i] != '\0')
	{
		if (input[i] == ' ')
			input[i] = '\1'; //change to \1
		i++;
	}
	return(i);
}

// TBD: maybe i need to copy string and free it after instead of changing an initial string
static int	preprosess_string(char *input)
{
	int	i;

	i = 0;
	while(input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = preprosess_quotes(input, i + 1, input[i]);
		if (input[i] == '\0')
		{
			unclosed_quote();
			return (-1);
		}
		i ++;
	}
	return(0);
}

static void	postprosess_array(t_minishell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->args[i] != NULL)
	{
		while (shell->args[i][j] != '\0')
		{
			if (shell->args[i][j] == '\1')
				shell->args[i][j] = ' ';
			j++;
		}
		j = 0;
		i++;
	}
}

void	parse_input(char *input, t_minishell *shell)
{
	int	i;

	i = preprosess_string(input);
	if (i != -1)
	{
		shell->args = ft_split(input, ' ');
		if (shell->args[0] == NULL) 
		{
			free(input);
			free(shell->args);
			shell->args = NULL;
		}
	}
	postprosess_array(shell);
}
