/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:47:06 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/26 00:38:13 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_single_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			s++;
		else
		{
			write (1, &s[i], 1);
			s++;
		}
	}
}

void	open_double_quotes(char *s)
{
	int	i;

	i = 0;
	

}

void	write_environmentals(char *s)
{
	

}


void	print_echo(t_minishell *shell, int i)
{
	char *single_quote;
	char *double_quote;

	while (shell->args[i])
	{
		single_quote = ft_strchr(shell->args[i], '\'');
    	double_quote = ft_strchr(shell->args[i], '\"');
		if (single_quote && (!double_quote || single_quote < double_quote))
		{
			open_single_quotes(shell->args[i]);
		}
		else if (double_quote && (!single_quote || double_quote < single_quote))
		{
			open_double_quotes(shell->args[i]);
		}
		else
			printf("%s", shell->args[i]);
		i ++;
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
