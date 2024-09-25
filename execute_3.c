/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:54:38 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/25 10:58:57 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminal_setup(struct termios orig_termios)
{
	struct termios	raw;

	raw = orig_termios;
	raw.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void	terminal_reset(struct termios orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

int	custom_read(void)
{
	char c;

	if(read(STDIN_FILENO, &c, 1) == 1)
		return (c);
	return EOF;	
}

void	setupfork(t_minishell *shell, t_args *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal_config_children();
	pid = fork();
	if (pid < 0)
	{
		error_exec();
		return ;
	}
	if (pid == 0)
		handle_cmd(shell, cmd);
	terminal_setup(shell->orig_termios);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else
		shell->exit_code = EXIT_FAILURE;
	terminal_reset(shell->orig_termios);
}

void	single_cmd(t_minishell *shell, t_args *cmd)
{
	expand_command(shell, cmd);
	if (cmd->cmd_valid == false)
		return ;
	if (handle_heredoc(cmd, shell) == 1)
	{
		shell->exit_code = 2;
		return ;
	}
	if (cmd->args == NULL || cmd->args[0] == NULL)
		return ;
	if (scanifbuiltin(cmd) == 1)
	{
		save_fds(shell);
		if (check_redirections(cmd) == 1)
		{
			shell->exit_code = EXIT_FAILURE;
			return ;
		}
		shell->exit_code = execbuiltin(shell, cmd);
		reset_fds(shell);
		return ;
	}
	setupfork(shell, cmd);
}
