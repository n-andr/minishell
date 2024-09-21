/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:41:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/21 17:12:43 by lde-taey         ###   ########.fr       */
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
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
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

int	handle_output_redirection(t_args *command, int *i)
{
	if (!command->redir[*i + 1])
	{
		ft_putstr_fd("syntax error near unexpected", STDERR_FILENO);
		ft_putendl_fd(" token `newline'", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (handle_rights(command->redir[*i], command->redir[*i + 1]) \
		== EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (command->redir[*i + 2] && \
		(ft_strncmp(command->redir[*i + 2], ">", 1) != 0) && \
		ft_strncmp(command->redir[*i + 2], "<", 1) != 0)
	{
		if (handle_rights(command->redir[*i], command->redir[*i + 2]) \
			== EXIT_FAILURE)
			return (EXIT_FAILURE);
		*i = *i + 1;
	}
	return (EXIT_SUCCESS);
}

int	handle_input_redirection(t_args *command, int *i)
{
	if (!command->redir[*i + 1])
	{
		ft_putendl_fd("error near unexpected token `newline'", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (handle_lefts(command->redir[*i + 1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (command->redir[*i + 2] && \
		ft_strncmp(command->redir[*i + 2], "<", 1) != 0 && \
		ft_strncmp(command->redir[*i + 2], ">", 1) != 0)
	{
		if (handle_lefts(command->redir[*i + 2]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		*i = *i + 1;
	}
	return (EXIT_SUCCESS);
}

int	redirection_loop(t_args *command)
{
	int	i;

	i = 0;
	while (command->redir[i] != NULL)
	{
		if (ft_strcmp(command->redir[i], "<") == 0)
		{
			if (handle_input_redirection(command, &i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (ft_strcmp(command->redir[i], "<<") == 0)
		{
			if (handle_lefts(command->heredoc) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (ft_strcmp(command->redir[i], ">") == 0 \
			|| ft_strcmp(command->redir[i], ">>") == 0)
		{
			if (handle_output_redirection(command, &i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
