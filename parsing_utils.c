/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:02:54 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/28 00:54:26 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_name(char c, int *i)
{
	if (!ft_isalnum(c) && c != '_' && c != '?')
	{
		(*i)++;
		return (false);
	}
	return (true);
}

char	*get_exit_code(t_minishell *shell, int *i)
{
	char	*exit_code;

	exit_code = ft_itoa(shell->exit_code);
	(*i)++;
	return (exit_code);
}

char	*empty_result_check(char *result, char *arg)
{
	int		i;
	bool	quote;

	quote = false;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"' || arg[i] == '\'')
		{
			quote = true;
			break ;
		}
		i++;
	}
	free(result);
	if (quote == true)
		return (ft_strdup(""));
	else
		return (NULL);
}

char	*free_and_assign(char *result, char *temp, char *substing)
{
	free(result);
	free(substing);
	result = temp;
	return (result);
}
