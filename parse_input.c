/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:00:10 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/17 00:17:05 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	empty_args(t_minishell *shell)
{
	free(shell->args);
	shell->args = NULL;
	shell->exit_code = 0;
	return (0);
}

int	parse_input(char *input, t_minishell *shell)
{
	int		i;
	char	*temp;

	temp = malloc(ft_strlen(input) + 1);
	if (!temp)
		return (-1);
	ft_strlcpy(temp, input, ft_strlen(input) + 1);
	free(input);
	i = preprosess_string(&temp);
	if (i == -1)
	{
		free(temp);
		shell->exit_code = 2;
		return (-1);
	}
	shell->args = ft_split(temp, ' ');
	free(temp);
	if (shell->args[0] == NULL)
		return (empty_args(shell));
	postprosess_array(shell);
	organize_struct(shell);
	free_array(shell->args);
	shell->args = NULL;
	return (1);
}
