/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:51:26 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/16 23:47:18 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_exists(char *arg, int name_len, char *new_var, t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->envs[i] != NULL)
	{
		if (ft_strncmp(shell->envs[i], arg, name_len) == 0)
		{
			free(shell->envs[i]);
			shell->envs[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

// needs to be implemented by upper/lower case and alpabetically
char	**realloc_env_array(char **envs, char *new_var)
{
	int		i;
	int		j;
	int		size;
	char	**new_envs;

	i = 0;
	j = 0;
	size = 0;
	while (envs[size] != NULL)
		size++;
	new_envs = malloc(sizeof(char *) * (size + 2));
	if (!new_envs)
		return (NULL);
	while (i < size && ft_strcmp(envs[i], new_var) < 0)
	{
		new_envs[j++] = envs[i++];
	}
	new_envs[j++] = new_var;
	while (i < size)
	{
		new_envs[j++] = envs[i++];
	}
	new_envs[j] = NULL;
	free(envs);
	return (new_envs);
}

int	check_var_name(char *arg)
{
	int	i;

	if (arg[0] != '_' && ft_isalpha(arg[0]) != 1)
		return (0);
	i = 1;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]) != 1 && arg[i] != '_')
			return (0);
		i++;
	}
	return (i);
}

int	process_var(t_args *cmd, t_minishell *shell, int i)
{
	int	name_len;
	int	exit_status;

	name_len = 0;
	exit_status = 0;
	while (cmd->args[i])
	{
		name_len = check_var_name(cmd->args[i]);
		if (name_len > 0)
			add_var(cmd->args[i], name_len, shell);
		else
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(cmd->args[i], STDERR_FILENO);
			ft_putstr_fd("`: not a valid identifier\n", STDERR_FILENO);
			exit_status = 1;
		}
		i++;
	}
	return (exit_status);
}

int	mini_export(t_minishell *shell, t_args *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "export") == 0)
	{
		i ++;
		if (cmd->args[i])
		{
			return (process_var(cmd, shell, i));
		}
		else
		{
			while (shell->envs[i] != NULL)
			{
				write(1, "declare -x ", 11);
				write(1, shell->envs[i], ft_strlen(shell->envs[i]));
				write(1, "\n", 1);
				i++;
			}
		}
	}
	return (0);
}

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

// 1. Check if name is ok, check if it exists in the list, 
//check if value is ok, 
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