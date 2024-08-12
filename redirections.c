/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:41:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/12 15:44:51 by lde-taey         ###   ########.fr       */
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

int	check_redirections(t_args *command)
{
	int i;
	
	i = 0;
	while(command->redir[i] != NULL)
	{
		if(ft_strcmp(command->redir[i], "<") == 0)
		{
			if (!command->redir[i + 1])
				return (0);
			if (!handle_lefts(command->redir[i + 1]))
				return (0);
		}
		else if(ft_strcmp(command->redir[i], "<<") == 0)
		{
			if (!handle_lefts(command->heredoc))
				return (0);
		}
		else if(ft_strcmp(command->redir[i], ">") == 0 \
			|| ft_strcmp(command->redir[i], ">>") == 0)
		{
			if (!command->redir[i + 1])
				return (0);
			if (!handle_rights(command->redir[i], command->redir[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}
