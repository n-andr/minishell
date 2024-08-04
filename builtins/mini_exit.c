/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:09:29 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/05 01:42:59 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// feel free to delete

#include "minishell.h"

// check if input is valid for exit command
// check if ft_atoi is enough to convert the string to int or if it is a number only

int check_if_number(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
	}
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			printf("exit\n"); //confirm on school computer if this is the right way to print
			printf("minishell: exit: %s: numeric argument required\n", str); //shell's intended output format (e.g., using fprintf(stderr, ...) for error messages).
			//exit(error code); and free everything
			return(0); 
		}
		i++;
	}
	return (1);
}

int	check_if_no_more_args(t_minishell *shell)
{
	if (shell->commands->args[2] != NULL)
	{
		printf("exit\n"); //confirm on school computer if this is the right way to print
		printf("exit: too many arguments\n"); //shell's intended output format (e.g., using fprintf(stderr, ...) for error messages).
		//exit(error code); and free everything
		return (0);
	}
	return (1);
}

// 1 - all good, 0 - error
int check_exit_arg(t_minishell *shell)
{
	if (shell->commands->args[1] == NULL)
		return (1);
	else
	{
		if(check_if_number(shell->commands->args[1]) == 1 && check_if_no_more_args(shell) == 1)
			return (1);
		else
			return (0);
	}
	return (1);
}
int	mini_exit(t_minishell *shell)
{
	int i;

	i = 0;
	// check if input is valid for exit command
	if (check_exit_arg(shell) == 0)
		return (1);
	i = ft_atoi(shell->commands->args[1]);
	// free everything!!! don't know what exactly yet
	free_everything(shell);
	printf("exit\n");
	exit(i);
}