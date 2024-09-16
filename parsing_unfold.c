/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unfold.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:51:12 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/16 00:23:55 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *var_name, t_minishell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (shell->envs[i] != NULL)
	{
		if (ft_strncmp(shell->envs[i], var_name, len) == 0)
			return (ft_strdup(shell->envs[i] + len + 1));
		i++;
	}
	return (NULL);
}

static bool	is_valid_name(char c, int *i)
{
	if (!ft_isalnum(c) && c != '_' && c != '?')
	{
		(*i)++;
		return (false);
	}
	return (true);
}

static char	*get_exit_code(t_minishell *shell, int *i)
{
	char	*exit_code;

	exit_code = ft_itoa(shell->exit_code);
	(*i)++;
	return (exit_code);
}

char	*expand_variable(char *str, int *i, t_minishell *shell)
{
	char	*var_name;
	char	*var_value;
	int		start;
	int		len;

	start = (*i) + 1;
	if (is_valid_name(str[*i + 1], i) == false)
		return (ft_strdup("$"));
	(*i)++;
	if (str[*i] == '?')
		return (get_exit_code(shell, i));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	var_name = ft_substr(str, start, len);
	if (!var_name)
		return (NULL);
	var_value = get_env_value(var_name, shell);
	free(var_name);
	if (var_value)
		return (var_value);
	else
		return (ft_strdup(""));
}

char	*free_and_assign(char *result, char *temp, char *substing)
{
	free(result);
	free(substing);
	result = temp;
	return (result);
}

// get the substring from the start to the current position,
// then get the variable expanded value and add it to the substring
char	*getvar(char *str, int *i, t_minishell *shell, char *unfold)
{
	char	*temp;
	char	*var_expanded;

	var_expanded = expand_variable(str, i, shell);
	temp = ft_strjoin(unfold, var_expanded);
	unfold = free_and_assign(unfold, temp, var_expanded);
	return (unfold);
}

char	*unfold_double(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*unfolded;
	char	*temp;
	char	*substing;

	unfolded = ft_strdup("");
	start = ++(*i);
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			substing = ft_substr(str, start, *i - start);
			temp = ft_strjoin(unfolded, substing);
			unfolded = free_and_assign(unfolded, temp, substing);
			unfolded = getvar(str, i, shell, unfolded);
			start = *i;
		}
		else
			(*i)++;
	}
	substing = ft_substr(str, start, *i - start);
	temp = ft_strjoin(unfolded, substing);
	unfolded = free_and_assign(unfolded, temp, substing);
	(*i)++;
	return (unfolded);
}

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
char	*empty_result_check(char *result, char *arg)
{
	int		i;
	bool	quote;

	quote = false;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"')
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
	//bool	valid;ke

	//valid = true;
	expand_array(shell, command->args);
	expand_array(shell, command->redir);
	if (command->args != NULL && command->args[0] == NULL)
	{
		free_array(command->args);
		command->args = NULL;
	}
	
	check_if_cmd_valid(shell, command);

	//valid = check_if_cmd_valid(shell, command);
	// command->cmd_valid = valid;
	// if (valid == false && command->next == NULL)
	// 	shell->exit_code = 127;
	// else if (valid == true && command->next == NULL)
	// 	shell->exit_code = 0;
}
