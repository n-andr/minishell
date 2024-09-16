/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unfold.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:51:12 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/17 00:30:58 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*unfold_single(char *str, int *i)
{
	int		start;
	int		len;
	char	*unfolded;

	start = ++(*i);
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	len = *i - start;
	unfolded = ft_substr(str, start, len);
	(*i)++;
	return (unfolded);
}

// check if the result is empty, 
// check if the arg is empty or if it contains quotes
// Example $NON_EXISTANT_VAR returns NULL
// Example "$NON_EXISTANT_VAR" returns empty string ("\0")
// Example "" returns empty string ("\0")

char	*expand(t_minishell *shell, char *arg, int *i, char *result)
{
	char	*expanded;
	char	*temp;

	if (arg[*i] == '$')
	{
		expanded = expand_variable(arg, i, shell);
		temp = ft_strjoin(result, expanded);
		result = free_and_assign(result, temp, expanded);
	}
	else if (arg[*i] == '\'')
	{
		expanded = unfold_single(arg, i);
		temp = ft_strjoin(result, expanded);
		result = free_and_assign(result, temp, expanded);
	}
	else if (arg[*i] == '"')
	{
		expanded = unfold_double(arg, i, shell);
		temp = ft_strjoin(result, expanded);
		result = free_and_assign(result, temp, expanded);
	}
	return (result);
}

// check string char by char, if found $ or ' or " do the unfolding, 
//then continue checking till the end of the string
char	*unfold_argument(char *arg, t_minishell *shell)
{
	int		i;
	char	*result;
	char	*temp;
	char	single_char[2];

	i = 0;
	result = ft_strdup("");
	while (arg[i])
	{
		if (arg[i] == '$' || arg[i] == '\'' || arg[i] == '"')
			result = expand(shell, arg, &i, result);
		else
		{
			single_char[0] = arg[i];
			single_char[1] = '\0';
			temp = ft_strjoin(result, single_char);
			free(result);
			result = temp;
			i++;
		}
	}
	if (result == NULL || ft_strlen(result) == 0)
		result = empty_result_check(result, arg);
	return (result);
}

// example: $PWD"hi$PWD"hi'$PWD'
//cases covered:
// - nothing to do
// - unfold VAR into VARs value
// - keep % as %
// - unfold '' and keep VAR as name only
// - unfold "" and no Var
// - unfold "" and get VARs value

void	expand_array(t_minishell *shell, char **array)
{
	char	*result;
	int		i;
	int		k;

	i = 0;
	k = 0;
	result = NULL;
	while (array != NULL && array[i] != NULL)
	{
		result = unfold_argument(array[i], shell);
		free(array[i]);
		if (result == NULL)
		{
			k = i;
			while (array[k] != NULL)
			{
				array[k] = array[k + 1];
				k ++;
			}
			free(result);
		}
		else
			array[i++] = result;
	}
	return ;
}

void	expand_command(t_minishell *shell, t_args *command)
{
	expand_array(shell, command->args);
	expand_array(shell, command->redir);
	if (command->args != NULL && command->args[0] == NULL)
	{
		free_array(command->args);
		command->args = NULL;
	}
	check_if_cmd_valid(shell, command);
}
