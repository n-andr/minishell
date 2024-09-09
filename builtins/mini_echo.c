/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:47:06 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/06 15:44:50 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(t_args *cmd, int i)
{
	if (cmd->heredoc != NULL)
	{
		char	buffer[1024];
    	ssize_t	bytes_read;

		while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) 
		{
			write(STDOUT_FILENO, buffer, bytes_read);	
		}
	}
	while (cmd->args[i] != NULL)
	{
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i])); 
		if (cmd->args[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1); 
		i++;
	}
}

int	check_flags(t_args *cmd, int i)
{
	int j;

	j = 0;
	while(cmd->args[i] && cmd->args[i][j] == '-')
	{
		j++;
		while (cmd->args[i][j] != '\0')
		{
			if (cmd->args[i][j] == 'n')
			{
				j++;
			}
			else
				return (i);
		}
		i++;
		j = 0;
	}
	return (i);
}

int		mini_echo(t_args *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "echo") == 0)
	{
		i++;
		if (check_flags(cmd, i) != i || cmd->heredoc != NULL)
		{
			i = check_flags(cmd, i);
			print_echo(cmd, i);
			//free_args(cmd);
			return (0);
		}
		else
		{
			print_echo(cmd, i);
			write (STDOUT_FILENO, "\n", 1);
			//free_args(cmd);
			return (0);
		}
	}
	return (1);
}
