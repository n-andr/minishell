/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:05:24 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/23 17:49:26 by lde-taey         ###   ########.fr       */
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

int	cleanup_rl(char *line, int fd)
{
	if (line)
		free(line);
	close (fd);
	return (1);
}

static int	generate_heredoc(t_args *command, char *delimiter)
{
	int		fd;
	char	*line;

	command->heredoc = generate_filename();
	while (1)
	{
		g_sigint_received = 0;
		fd = open(command->heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (0);
		while (g_sigint_received == 0)
		{
			line = readline(">");
			if (!line || ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0)
				return (cleanup_rl(line, fd));
			ft_putendl_fd(line, fd);
			free(line);
		}
		close(fd);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
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
