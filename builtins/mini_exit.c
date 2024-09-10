/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:09:29 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/05 16:03:32 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			ft_putendl_fd("minishell: exit: numeric argument required", STDERR_FILENO);
			return(2); // exit(2)
		}
		i++;
	}
	return (ft_atoi(str));
}

void	mini_exit(t_minishell *shell)
{
	int exit_code;

	exit_code = 0;
	printf("exit\n"); //confirm on school computer if this is the right way to print for all cases
	// check if input is valid for exit command
	if(shell->commands->args[1] == NULL)
	{
		exit_code = 0;
	}
	else if(shell->commands->args[2] == NULL)
	{
		exit_code = check_if_number(shell->commands->args[1]);
	}
	else
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		exit_code = 1; //exit(EXIT_FAILURE);
	}
	free_everything(shell);
	// printf("This is the exit_code: %i\n", exit_code);
	exit(exit_code);
}
