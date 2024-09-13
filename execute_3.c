/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:54:38 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/13 18:09:26 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setupfork(t_minishell *shell, t_args *cmd)
{
	pid_t	pid;
	int		status;

	signal_config_execute();
	pid = fork();
	if (pid < 0)
	{
		error_exec();
		return ;
	}
	if (pid == 0)
		handle_cmd(shell, cmd);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else
		shell->exit_code = EXIT_FAILURE;
}

void	single_cmd(t_minishell *shell, t_args *cmd)
{
	expand_command(shell, cmd);
	if (cmd->cmd_valid == false)
		return ;
	if (handle_heredoc(cmd) == 1)
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
