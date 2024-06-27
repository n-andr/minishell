/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:41:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/27 16:40:04 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_rights(char *signs, char *file)
{
	int	fd;

	if (!ft_strcmp(signs, ">>"))
		fd = open(file, O_WRONLY | O_APPEND);
	else
		fd = open(file, O_WRONLY);
	if (fd < 0)
	{
		perror("Error. failed to open file");
		return (0);
	}
	if (fd < 0 && dup2(fd, 1) < 0)
	{
		perror("Error. failed to open file");
		return (0);
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
	if (fd > 0 && dup2(fd, 0) < 0)
	{
		perror("Error. failed to open file");
		return (0);
	}
	close(fd);
	return (1);
}

int	check_redirections(t_minishell *shell)
{
	shell->redir[0] = ft_strdup(">>"); // do this differently, segfaults now
	shell->redir[1] = ft_strdup ("test.txt");	
	shell->redir[2] = ft_strdup ("");
	int i;
	
	i = 0;
	while(shell->redir[i] != NULL)
	{
		if(!ft_strcmp(shell->redir[i], "<<"))
		{
			if (!handle_lefts(shell->redir[i + 1]))
				return (0);
		}
		else if(!ft_strcmp(shell->redir[i], "<"))
		{
			if (!handle_lefts(shell->heredoc))
				return (0);
		}
		else if(!ft_strcmp(shell->redir[i], ">") \
			|| !ft_strcmp(shell->redir[i], ">>"))
		{
			if (!handle_rights(shell->redir[i], shell->redir[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}
