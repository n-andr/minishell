/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:41:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/04 13:57:26 by lde-taey         ###   ########.fr       */
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
	shell->redir = (char **)malloc((3) * sizeof(char *));
	shell->redir[0] = ">";
	shell->redir[1] = "test.txt";	
	shell->redir[2] = NULL;
	int i;
	
	i = 0;
	while(shell->redir[i] != NULL)
	{
		if(ft_strncmp(shell->redir[i], "<<", 2) == 0)
		{
			if (!handle_lefts(shell->redir[i + 1]))
				return (0);
		}
		else if(ft_strncmp(shell->redir[i], "<", 1) == 0)
		{
			if (!handle_lefts(shell->heredoc))
				return (0);
		}
		else if(ft_strncmp(shell->redir[i], ">", 1) == 0 \
			|| ft_strncmp(shell->redir[i], ">>", 2) == 0)
		{
			if (!handle_rights(shell->redir[i], shell->redir[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}
