/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:47:06 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/26 16:10:33 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_echo(t_args *cmd, int i)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	bytes_read = 1;
	if (cmd->heredoc != NULL)
	{
		while (bytes_read > 0)
		{
			bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
			if (bytes_read < 0)
				break ;
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
	int	j;

	j = 0;
	while (cmd->args[i] && cmd->args[i][j] == '-')
	{
		j++;
		if (cmd->args[i][j] == '\0')
		{
			return (i);
		}
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

int	mini_echo(t_args *cmd)
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
			return (0);
		}
		else
		{
			print_echo(cmd, i);
			write (STDOUT_FILENO, "\n", 1);
			return (0);
		}
	}
	return (1);
}
