/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:41:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/05 15:54:11 by lde-taey         ###   ########.fr       */
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
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("Error. failed to open file");
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}

int	handle_lefts(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error. failed to open file");
		return (0);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		perror("Error. failed to open file");
		return (0);
	}
	close(fd);
	return (1);
}

int	check_redirections(t_minishell *shell)
{
	/* shell->commands = malloc(sizeof(t_args));
	shell->commands->redir = (char **)malloc((3) * sizeof(char *));
	shell->commands->redir[0] = "<<";
	shell->commands->redir[1] = "EOF";	
	shell->commands->redir[2] = NULL; */
	int i;
	
	i = 0;
	while(shell->commands->redir[i] != NULL)
	{
		if(ft_strcmp(shell->commands->redir[i], "<") == 0)
		{
			if (!shell->commands[0].redir[i + 1])
				return (0);
			if (!handle_lefts(shell->commands[0].redir[i + 1])) // checken of dit klopt, invalid read
				return (0);
		}
		else if(ft_strcmp(shell->commands->redir[i], "<<") == 0)
		{
			if (!handle_lefts(shell->commands[0].heredoc))
				return (0);
		}
		else if(ft_strcmp(shell->commands->redir[i], ">") == 0 \
			|| ft_strcmp(shell->commands->redir[i], ">>") == 0)
		{
			if (!shell->commands[0].redir[i + 1])
				return (0);
			if (!handle_rights(shell->commands->redir[i], shell->commands->redir[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}
