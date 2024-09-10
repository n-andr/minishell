/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:05:24 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/09 13:33:12 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_filename(void)
{
	char		*filename;
	char		*number;
	static int	nbr;

	number = ft_itoa(nbr);
	nbr += 1;
	filename = ft_strjoin("./heredoc_file_", number);
	free(number);
	return (filename); // TODO delete + free filename
}

static int	generate_heredoc(t_args *command, char *delimiter)
{
	int		fd;
	char	*line;

	command->heredoc = generate_filename();
	fd = open(command->heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	line = readline(">");
	while (line && ft_strncmp(delimiter, line, ft_strlen(delimiter)))
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

int	handle_heredoc(t_args *command)
{
	int	i;

	i = 0;
	if(command->is_redir == 0)
		return (EXIT_SUCCESS);
	while (command->redir[i] != NULL)
	{
		if (!ft_strncmp(command->redir[i], "<<", 2))
		{
			if(!command->redir[i + 1])
			{
				ft_putendl_fd("syntax error near unexpected token `newline'", STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			if (!generate_heredoc(command, command->redir[i + 1]))
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
 