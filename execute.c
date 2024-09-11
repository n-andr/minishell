/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:23:44 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/12 22:06:27 by nandreev         ###   ########.fr       */
/*   Updated: 2024/09/11 14:55:44 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop_through_paths(t_minishell *shell, char *cmd, t_args *command)
{
	int		i;
	char	*newcmd;
	char	*tmp;

	i = 0;
	while (shell->paths[i] != NULL)
	{
		tmp = ft_strjoin(shell->paths[i], "/");
		newcmd = ft_strjoin(tmp, cmd);
		free (tmp);
		if (!access(newcmd, F_OK))
			execve(newcmd, command->args, shell->envs);
		i++;
	}
	directory_check(shell, newcmd);
	command_check(shell, newcmd);
	free(newcmd);
}

void	check_paths_and_command(char *cmd, t_args *command, t_minishell *shell)
{
	if (!access(cmd, F_OK))
	{
		execve(cmd, command->args, shell->envs);
		directory_check(shell, cmd);
		command_check(shell, cmd);
	}
	else
		loop_through_paths(shell, cmd, command);
}

void	handle_cmd(t_minishell *shell, t_args *command)
{
	char	*cmd;

	expand_command(shell, command);
	if (command->cmd_valid == false)
		return ;
	if (check_redirections(command) == 1)
		exit(EXIT_FAILURE);
	if (scanifbuiltin(command) == 1)
	{
		execbuiltin(shell, command);
		exit(EXIT_SUCCESS);
	}
	cmd = ft_strdup(command->args[0]);
	check_paths_and_command(cmd, command, shell);
	free(cmd);
}

void	execute(t_minishell *shell)
{
	if (!shell->commands)
	{
		free_commands(shell);
		return ;
	}
	if (shell->commands->is_pipe == 0)
	{
		single_cmd(shell, shell->commands);
		free_commands(shell);
		return ;
	}
	else if (shell->commands->next)
		ft_pipe(shell);
	free_commands(shell);
}
