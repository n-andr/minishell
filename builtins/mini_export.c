/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:51:26 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/29 13:24:32 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// to do

int	process_arg(char *arg)
{
	// look for = sign
	int eq_pos;

	eq_pos = ft_strchr(arg, '=');
	if (!eq_pos)
	{
		// if no value is provided - export the var with its current value
	}
	else
	{
		// if the var doesn't exist: add var to env
		// if it does exist: assign new value with setenv (maybe avoid setenv)
	}
}

int	check_if_valid(char *arg)
{
	// check only part before equal sign
	
	int i;
	char *eq_pos;
	
	eq_pos = ft_strchr(arg, '=');
	// arg - *eq_pos = '\0';
	
	if(arg[0] != '_' && ft_isalpha(arg[0]) != 1)
		return (0);
	i = 1;
	while(arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]) != 1 || arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	mini_export(t_minishell *shell)
{
	int i;
	
	i = 0;
	if (shell->commands->args[1])
	{
		while (shell->commands->args[1 + i])
		{
			if (check_if_valid(shell->commands->args[1 + i]) == 1)
				process_arg(shell->commands->args[1 + i]); // separate name and value
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
		}
	}
	return (0);
}