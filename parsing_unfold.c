/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unfold.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:51:12 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/11 20:16:19 by nandreev         ###   ########.fr       */
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

char	*expand_variable(char *str, int *i, t_minishell *shell)
{
	char	*var_name;
	char	*var_value;
	int		start;
	int		len;

	start = (*i) + 1;
	if (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_' 
		&& str[*i + 1] != '?')
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	(*i)++;
	if (str[*i] == '?')
	{
		var_value = ft_itoa(shell->exit_code);
		(*i)++;
		return (var_value);
	}
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

char	*unfold_double(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*unfolded;
	char	*temp;
	char	*var_expanded;
	char	*substing;

	unfolded = ft_strdup("");
	start = ++(*i); 
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			substing = ft_substr(str, start, *i - start);
			temp = ft_strjoin(unfolded, substing);
			free(unfolded);
			free(substing);
			unfolded = temp;
			var_expanded = expand_variable(str, i, shell);
			temp = ft_strjoin(unfolded, var_expanded);
			free(unfolded);
			free(var_expanded);
			unfolded = temp;
			start = *i;
		}
		else
			(*i)++;
	}
	substing = ft_substr(str, start, *i - start);
	temp = ft_strjoin(unfolded, substing);
	free(unfolded);
	free(substing);
	unfolded = temp;
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
	int	i;
	bool	quote;

	quote = false;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '"')
		{
			quote = true;
			break;
		}
		i++;
	}
	free(result);
	if (quote == true)
		return (ft_strdup(""));
	else
		return (NULL);
}

// check string char by char, if found $ or ' or " do the unfolding, then continue checking till the end of the string
char	*unfold_argument(char *arg, t_minishell *shell)
{
	int		i;
	char	*result;
	char	*temp;
	char	*expanded;
	char	single_char[2];

	i = 0;
	result = ft_strdup("");
	while (arg[i])
	{
		expanded = NULL;
		if (arg[i] == '$')
		{
			expanded = expand_variable(arg, &i, shell);
			temp = ft_strjoin(result, expanded);
			free(result);
			free(expanded);
			result = temp;
		}
		else if (arg[i] == '\'')
		{
			expanded = unfold_single(arg, &i);
			temp = ft_strjoin(result, expanded);
			free(result);
			free(expanded);
			result = temp;
		}
		else if (arg[i] == '"')
		{
			expanded = unfold_double(arg, &i, shell);
			temp = ft_strjoin(result, expanded);
			free(result);
			free(expanded);
			result = temp;
		}
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
	if (result == NULL || ft_strlen(result) == 0 )
		result = empty_result_check(result, arg);
	return(result);
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
	int	i;
	int	k;

	i = 0;
	k = 0;
	result = NULL;
	while (array != NULL && array[i] != NULL)
	{
		result = unfold_argument(array[i], shell);
		free(array[i]);
		if(result == NULL)
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
		{
			array[i] = result;
			i ++;
		}
	}
	if (array != NULL && array[0] == NULL)
	{
		free_array(array);
		array = NULL;
	}	
	return;
}


void	expand_command(t_minishell *shell, t_args *command)
{
	bool	valid;

	valid = true;
	expand_array(shell, command->args);
	expand_array(shell, command->redir);
	//test_printf_command(command);
	if (command->args != NULL && command->args[0] == NULL)
	{
		free_array(command->args);
	}
	
	valid = check_if_cmd_valid(shell, command);
	command->cmd_valid = valid; //mabe not needed
	if (valid == false && command->next == NULL)
		shell->exit_code = 127;
	else if (valid == true && command->next == NULL)
		shell->exit_code = 0;
	
}

// void	unfold_struct(t_minishell *shell)
// {
// 	//int	i;
// 	// int k;
// 	// char	*result;
// 	t_args	*tmp;

// 	//i = 0;
// 	tmp = shell->commands;
// 	while (tmp != NULL)
// 	{
// 		expand_command(shell, tmp);
// 		// while (tmp->args != NULL && tmp->args[i] != NULL)
// 		// {
// 		// 	// printf("tmp->args[i]: %s \n", tmp->args[i]);
// 		// 	result = unfold_argument(tmp->args[i], shell);
// 		// 	// printf("result: %s \n", result);
// 		// 	free(tmp->args[i]);
// 		// 	if(result == NULL) //remove NULL string from the list of args
// 		// 	{
// 		// 		k = i;
// 		// 		while (tmp->args[k] != NULL)
// 		// 		{
// 		// 			tmp->args[k] = tmp->args[k + 1];
// 		// 			k ++;
// 		// 		}
// 		// 		free(result);
// 		// 	}
// 		// 	else
// 		// 	{
// 		// 		tmp->args[i] = result;
// 		// 		i ++;
// 		// 	}
// 		// }
// 		// if (tmp->args != NULL && tmp->args[0] == NULL)
// 		// {
// 		// 	free(tmp->args);
// 		// 	tmp->args = NULL;
// 		// }	
// 		// i = 0;
// 		// while (tmp->redir != NULL && tmp->redir[i] != NULL)
// 		// {
// 		// 	result = unfold_argument(tmp->redir[i], shell);
// 		// 	free(tmp->redir[i]);
// 		// 	if(result == NULL) //remove NULL string from the list of args
// 		// 	{
// 		// 		k = i;
// 		// 		while (tmp->redir[k] != NULL)
// 		// 		{
// 		// 			tmp->redir[k] = tmp->redir[k + 1];
// 		// 			k ++;
// 		// 		}
// 		// 	}
// 		// 	else
// 		// 	{
// 		// 		tmp->redir[i] = result;
// 		// 		i ++;
// 		// 	}
// 		// 	i ++;
// 		// }
// 		// if (tmp->redir != NULL && tmp->redir[0] == NULL)
// 		// {
// 		// 	free(tmp->redir);
// 		// 	tmp->is_redir = false;
// 		// 	tmp->redir = NULL;
// 		// }
// 		tmp = tmp->next;
// 	}
// }
