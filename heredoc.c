/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:05:24 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/04 16:57:20 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *generate_filename(void)
{
	char 		*filename;
	char		*number;
	static int	nbr;

	number = ft_itoa(nbr);
	nbr += 1;
	filename = ft_strjoin("./tmp_heredoc_file_", number);
	free(number);
	return (filename);
}

static int generate_heredoc(t_minishell *shell, char *delimiter)
{	
	int		fd;
	char	*line;
	
	shell->commands[0].heredoc = generate_filename();
	fd = open(shell->commands[0].heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	line = readline(">");
	while(line && ft_strncmp(delimiter, line, ft_strlen(delimiter)))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(">");
	}
	free(line);
	close (fd);
	return (1);
}

int	handle_heredoc(t_minishell *shell)
{	
	shell->commands = malloc(1 * sizeof(t_args));
	if (!shell->commands)
		return (-1);
	shell->commands[0].redir = (char **)malloc(3 * sizeof(char *));
	shell->commands[0].redir[0] = "<<";
	shell->commands[0].redir[1] = "EOF";	
	shell->commands[0].redir[2] = NULL;
	
	int	i;
	
	i = 0;
	while (shell->commands->redir[i] != NULL)
	{
		if (!ft_strncmp(shell->commands->redir[i], "<<", 2))
		{
			if (!generate_heredoc(shell, shell->commands->redir[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}
