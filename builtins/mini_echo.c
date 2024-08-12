/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:47:06 by nandreev          #+#    #+#             */
/*   Updated: 2024/08/08 21:58:27 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(t_minishell *shell, int i)
{
	while (shell->commands->args[i] != NULL)
	{
		write(1, shell->commands->args[i], ft_strlen(shell->commands->args[i])); //change to fd for pipes
		if (shell->commands->args[i + 1] != NULL)
			write(1, " ", 1); //change to fd for pipes
		i++;
	}
}

int	check_flags(t_minishell *shell, int i)
{
	int j;

	j = 0;
	while(shell->commands->args[i] && shell->commands->args[i][j] == '-')
	{
		j ++;
		
		while (shell->commands->args[i][j] != '\0')
		{
			if (shell->commands->args[i][j] == 'n')
			{
				j ++;
			}
			else
				return (i);
		}
		i++;
		j = 0;
	}
	return (i);
}

void	mini_echo(t_minishell *shell)
{
	int	i;

	i = 0;
	if (shell->commands->args[i] && ft_strcmp(shell->commands->args[i], "echo") == 0)
	{
		i++;
		if (check_flags(shell, i) != i)
		{
			i = check_flags(shell, i);
			print_echo(shell, i);
		}
		else
		{
			print_echo(shell, i);
			write (1, "\n", 1); //change to fd for pipes
		}
	}
	//free_args(shell);
}
