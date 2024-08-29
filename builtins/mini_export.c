/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:51:26 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/29 16:59:38 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// to do

// int	process_arg(char *arg)
// {
// 	// look for = sign
// 	int eq_pos;

// 	eq_pos = ft_strchr(arg, '=');
// 	if (!eq_pos)
// 	{
// 		// if no value is provided - export the var with its current value
// 	}
// 	else
// 	{
// 		// if the var doesn't exist: add var to env
// 		// if it does exist: assign new value with setenv (maybe avoid setenv)
// 	}
// }

// int	check_if_valid(char *arg)
// {
// 	// check only part before equal sign
	
// 	int i;
// 	char *eq_pos;
	
// 	eq_pos = ft_strchr(arg, '=');
// 	// arg - *eq_pos = '\0';
	
// 	if(arg[0] != '_' && ft_isalpha(arg[0]) != 1)
// 		return (0);
// 	i = 1;
// 	while(arg[i] != '\0')
// 	{
// 		if (ft_isalnum(arg[i]) != 1 || arg[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

int	mini_export(t_minishell *shell, t_args *cmd)
{
	int i;
	
	i = 0;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "export") == 0)
	{
		i ++;
		if (cmd->args[i])
		{
			while (cmd->args[i])
			{
				check name
				check existence if not - add
				check value - add value
				
				if (check_if_valid(cmd->args[i]) == 1)
					process_arg(cmd->args[i]); // separate name and value
				
				else
					write(STDERR_FILENO, "export: not a valid identifier", 31);
				i++;
			}
			
		}
		else
		{
			while(shell->envs[i] != NULL)
			{
				write(1, shell->envs[i], ft_strlen(shell->envs[i]));
				write(1, '\n', 1);
				i++;
			}
		}
	}
	return (0);
}

// int	mini_export(t_minishell *shell)
// {
// 	int i;
	
// 	i = 0;
// 	if (shell->commands->args[1])
// 	{
// 		while (shell->commands->args[1 + i])
// 		{
// 			if (check_if_valid(shell->commands->args[1 + i]) == 1)
// 				process_arg(shell->commands->args[1 + i]); // separate name and value
// 			else
// 				write(STDERR_FILENO, "export: not a valid identifier", 31);
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		while(shell->envs[i] != NULL)
// 		{
// 			write(1, shell->envs[i], ft_strlen(shell->envs[i]));
// 			write(1, '\n', 1);
// 			i++;
// 		}
// 	}
// 	return (0);
// }

// export [-fn] [-p] [name[=value]]

// export VAR=value
// export VAR - creates VAR
// export VAR= - creates VAR with empty value
// export VAR=VALUE - creates VAR with VALUE
// export var="value" - creates var with value
// export var='value' - creates var with value
// export var='value'01 - creates var with value01



// export var var2=testTest +val2
// val and var2 are valid, +val2 is not valid. 
// Export prosides first and second and returnes error for the third
// var1=""
// var2="testTest"
// bash: export: `+val2': not a valid identifier

// 1. Check if name is ok, check if it exists in the list, check if value is ok, 
// if it does, update it, if it doesn't add it alphabetically
// 2. Check i more than one argument is provided
// 3. If no arguments are provided, print all the variables



// example 
// declare -x USER="nandreev"
// declare -x VAR1
// declare -x VAR2
// declare -x VAR3=""

// Errors:
// not a valid variable name
// First letter is not a letter or underscore
// Contains characters other than letters, numbers, and underscores
// not a valid identifier ()

// Examples:
// export -bla
// bash: export: -b: invalid option
// export var1 +val2
// bash: export: `+val2': not a valid identifier



// Return
// The return status is zero unless an invalid option is supplied, 
// one of the names is not a valid shell variable name, 
// or -f is supplied with a name that is not a shell function. 