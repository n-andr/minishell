/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unfold.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:51:12 by nandreev          #+#    #+#             */
/*   Updated: 2024/07/08 03:00:29 by nandreev         ###   ########.fr       */
/*   Updated: 2024/07/10 01:54:56 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char *str, int *i)
{
	char	*var_name;
	char	*var_value;
	int		start;
	int		len;

	start = (*i) + 1;
	if (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_')
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	(*i)++;
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
		return ft_strdup(var_value);
	else
		return ft_strdup("");
}

char	*unfold_double(char *str, int *i)
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
			var_expanded = expand_variable(str, i);
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

// check string char by char, if found $ or ' or " do the unfolding, then continue checking till the end of the string
char	*unfold_argument(char *arg)
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
			temp = ft_strjoin(result, expand_variable(arg, &i));
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
			temp = ft_strjoin(result, unfold_double(arg, &i));
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

void print_args(t_minishell *shell, char *comment)
{
	//delete me
	int i = 0;
	printf("%s\n", comment);
	while (shell->args[i])
	{
		printf("%s\n", shell->args[i]);
		i++;
	}
	
}

void	unfold_input(t_minishell *shell)
{
	int	i;
	int k;
	char	*result;

	i = 0;
	//print_args(shell, "old"); //delete
	while (shell->args[i] != NULL)
	{
		//check if i even need to unfold/expand anything in the current arg
		//maybe save straight to struct?
		result = unfold_argument(shell->args[i]);
		free(shell->args[i]);
		// if(result == NULL) if we want to keep empty strings
		if(result == NULL || ft_strlen(result) == 0) //remove string from the list of args
		{
			k = i;
			while (shell->args[k] != NULL)
			{
				shell->args[k] = shell->args[k + 1];
				k ++;
			}
		}
		else
		{
			shell->args[i] = result;
			i ++;
		}
	}
	//print_args(shell, "new"); //delete
}
