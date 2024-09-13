/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:05:24 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/13 12:43:03 by lde-taey         ###   ########.fr       */
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
	return (filename);
}

static int	generate_heredoc(t_args *command, char *delimiter)
{
	int		fd;
	char	*line;

	g_sigint_received = 0;
	command->heredoc = generate_filename();
	fd = open(command->heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (0);
	line = readline(">");
	while (line && ft_strncmp(delimiter, line, ft_strlen(delimiter)))
	{
		/* if (g_sigint_received != 0)
		{
			free(line);
			g_sigint_received = 0;
			ft_putstr_fd("\n", STDOUT_FILENO); // how to erase all the lines and start a new file? // double free detected now
			return (0);
		}
		else
		{*/
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free(line);
			line = readline(">");
		//}
	}
	free(line);
	close (fd);
	return (1);
}

int	handle_heredoc(t_args *command)
{
	int	i;

	i = 0;
	if (command->is_redir == 0)
		return (EXIT_SUCCESS);
	while (command->redir[i] != NULL)
	{
		if (!ft_strncmp(command->redir[i], "<<", 2))
		{
			signal_config_heredoc();
			if (!command->redir[i + 1])
			{
				ft_putstr_fd("syntax error near ", STDERR_FILENO);
				ft_putendl_fd("unexpected token `newline'", STDERR_FILENO);
				return (EXIT_FAILURE);
			}
			if (!generate_heredoc(command, command->redir[i + 1]))
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
