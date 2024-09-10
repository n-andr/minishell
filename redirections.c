/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:41:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/09 16:24:14 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_rights(char *signs, char *file)
{
	int	fd;

	if (!ft_strcmp(signs, ">>"))
		fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error. failed to open file");
		return (EXIT_FAILURE);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("Error. failed to open file");
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	handle_lefts(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error. failed to open file");
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		perror("Error. failed to open file");
		return (EXIT_FAILURE);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int	check_redirections(t_args *command)
{
	int i;
	
	i = 0;
	if (!command->redir)
		return (EXIT_SUCCESS);
	while(command->redir[i] != NULL)
	{
		if(ft_strcmp(command->redir[i], "<") == 0)
		{
			if (!command->redir[i + 1])
			{
				ft_putendl_fd("error near unexpected token `newline'", STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			if (handle_lefts(command->redir[i + 1]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			while (command->redir[i + 2] && ft_strncmp(command->redir[i + 2], "<", 1) != 0 && \
				ft_strncmp(command->redir[i + 2], ">", 1) != 0)
			{
				if (handle_lefts(command->redir[i + 2]) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				i++;
			}
		}
		else if(ft_strcmp(command->redir[i], "<<") == 0)
		{
			if (handle_lefts(command->heredoc) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if(ft_strcmp(command->redir[i], ">") == 0 \
			|| ft_strcmp(command->redir[i], ">>") == 0)
		{
			if (!command->redir[i + 1])
			{
				ft_putendl_fd("error near unexpected token `newline'", STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			if (handle_rights(command->redir[i], command->redir[i + 1]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			while (command->redir[i + 2] && (ft_strncmp(command->redir[i + 2], ">", 1) != 0) && \
				ft_strncmp(command->redir[i + 2], "<", 1) != 0)
			{
				if (handle_rights(command->redir[i], command->redir[i + 2]) == EXIT_FAILURE)
					return (EXIT_FAILURE);
				i++;
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	save_fds(t_minishell *shell)
{
	shell->fds->stdin = dup(STDIN_FILENO);
	shell->fds->stdout = dup(STDOUT_FILENO);
}

void	reset_fds(t_minishell *shell)
{
	dup2(shell->fds->stdin, STDIN_FILENO);
	dup2(shell->fds->stdout, STDOUT_FILENO);
	close(shell->fds->stdin);
	close(shell->fds->stdout);
}
