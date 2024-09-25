/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:05:24 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/25 15:50:50 by lde-taey         ###   ########.fr       */
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

int	cleanup_rl(char *line, int *fd)
{
	if (line)
		free(line);
	close (*fd);
	return (1);
}

int	readline_loop(t_minishell *shell, char *delimiter, int *fd)
{
	char	*line;

	g_sigint_received = 0;
	while (g_sigint_received == 0)
	{
		line = readline(">");
		if (!line)
		{
			write (STDOUT_FILENO, "exit\n", 5);
			free_everything(shell);
			exit(0);
		}
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0)
			return (cleanup_rl(line, fd));
		ft_putendl_fd(line, *fd);
		free(line);
	}
	return (0);
}

static int	generate_heredoc(t_args *cmd, char *delimiter, t_minishell *shell)
{
	int		fd;

	cmd->heredoc = generate_filename();
	while (1)
	{
		fd = open(cmd->heredoc, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (0);
		if (readline_loop(shell, delimiter, &fd))
			break ;
		close(fd);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (1);
}

int	handle_heredoc(t_args *command, t_minishell *shell)
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
			if (!generate_heredoc(command, command->redir[i + 1], shell))
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
