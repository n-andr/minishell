/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:47:06 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/25 22:55:58 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_echo(t_minishell *shell, int i)
{
	while (shell->args[i])
	{
		if (ft_strchr())
	}
	

}

void	execute_echo(t_minishell *shell)
{
	int	i;

	i = 0;
	if (shell->args[i] && ft_strcmp(shell->args[i], "echo") == 0)
	{
		i ++;
		if (shell->args[i] && ft_strcmp(shell->args[i], "-n") == 0)
		{
			print_echo(shell, i++);
		}
		else if(shell->args[i] && ft_strcmp(shell->args[i], "-n") != 0)
		{
			print_echo(shell, i);
			write (1, '\n', 1);
		}
		else
			write (1, '\n', 1);
	}
	free_args(shell);
}
