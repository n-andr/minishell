/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unfold.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:51:12 by nandreev          #+#    #+#             */
/*   Updated: 2024/08/27 19:21:29 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (ft_strdup(var_value));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	var_name = ft_substr(str, start, len);
	if (!var_name)
		return (NULL);
	var_value = getenv(var_name);
	free(var_name);
	//return (var_value ? ft_strdup(var_value) : ft_strdup(""));
	if (var_value)
		return (ft_strdup(var_value));
	else
		return (ft_strdup(""));
}

char	*unfold_double(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*unfolded;
	char	*temp;
	char	*var_expanded;

	unfolded = ft_strdup("");
	start = ++(*i); 
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			temp = ft_strjoin(unfolded, ft_substr(str, start, *i - start));
			free(unfolded);
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
	temp = ft_strjoin(unfolded, ft_substr(str, start, *i - start));
	free(unfolded);
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
	char	single_char[2];

	i = 0;
	result = ft_strdup("");
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			temp = ft_strjoin(result, expand_variable(arg, &i, shell));
			free(result);
			result = temp;
		}
		else if (arg[i] == '\'')
		{
			temp = ft_strjoin(result, unfold_single(arg, &i));
			free(result);
			result = temp;
		}
		else if (arg[i] == '"')
		{
			temp = ft_strjoin(result, unfold_double(arg, &i, shell));
			free(result);
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
		// printf("array[i]: %s \n", array[i]);
		result = unfold_argument(array[i], shell);
		// printf("result: %s \n", result);
		free(array[i]);
		if(result == NULL) //remove NULL string from the list of args
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
		free(array);
		array = NULL;
	}	
	return;
}

void	expand_command(t_minishell *shell, t_args *command)
{
	expand_array(shell, command->args);
	expand_array(shell, command->redir);
	printf("command after expantion\n");
	test_printf_command(command);
	//shell->exit_code = 0; not here, after all command are done
}

void	unfold_struct(t_minishell *shell)
{
	int	i;
	// int k;
	// char	*result;
	t_args	*tmp;

	i = 0;
	tmp = shell->commands;
	while (tmp != NULL)
	{
		expand_command(shell, tmp);
		// while (tmp->args != NULL && tmp->args[i] != NULL)
		// {
		// 	// printf("tmp->args[i]: %s \n", tmp->args[i]);
		// 	result = unfold_argument(tmp->args[i], shell);
		// 	// printf("result: %s \n", result);
		// 	free(tmp->args[i]);
		// 	if(result == NULL) //remove NULL string from the list of args
		// 	{
		// 		k = i;
		// 		while (tmp->args[k] != NULL)
		// 		{
		// 			tmp->args[k] = tmp->args[k + 1];
		// 			k ++;
		// 		}
		// 		free(result);
		// 	}
		// 	else
		// 	{
		// 		tmp->args[i] = result;
		// 		i ++;
		// 	}
		// }
		// if (tmp->args != NULL && tmp->args[0] == NULL)
		// {
		// 	free(tmp->args);
		// 	tmp->args = NULL;
		// }	
		// i = 0;
		// while (tmp->redir != NULL && tmp->redir[i] != NULL)
		// {
		// 	result = unfold_argument(tmp->redir[i], shell);
		// 	free(tmp->redir[i]);
		// 	if(result == NULL) //remove NULL string from the list of args
		// 	{
		// 		k = i;
		// 		while (tmp->redir[k] != NULL)
		// 		{
		// 			tmp->redir[k] = tmp->redir[k + 1];
		// 			k ++;
		// 		}
		// 	}
		// 	else
		// 	{
		// 		tmp->redir[i] = result;
		// 		i ++;
		// 	}
		// 	i ++;
		// }
		// if (tmp->redir != NULL && tmp->redir[0] == NULL)
		// {
		// 	free(tmp->redir);
		// 	tmp->is_redir = false;
		// 	tmp->redir = NULL;
		// }
		tmp = tmp->next;
	}
}
