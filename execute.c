/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:23:44 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/10 15:52:00 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cmd(t_minishell *shell, t_args *command)
{
	char	*cmd;
	char	*tmp;
	char	*newcmd;
	int		i;

	// expand_command and check if valid
	if (check_redirections(command) == 1)
		exit(EXIT_FAILURE);
	if (scanifbuiltin(command) == 1)
	{
		execbuiltin(shell, command);
		exit(EXIT_SUCCESS);
	}
	cmd = ft_strdup(command->args[0]);
	i = 0;
	if (!access(cmd, F_OK))
	{
		execve(cmd, command->args, shell->envs);
		directory_check(shell, cmd);
		command_check(shell, cmd);
	}
	else
	{
		while (shell->paths[i] != NULL)
		{
			tmp = ft_strjoin(shell->paths[i], "/");
			newcmd = ft_strjoin(tmp, cmd);
			if (!access(newcmd, F_OK))
				execve(newcmd, command->args, shell->envs);
			i++;
			//free stuff
		}
		directory_check(shell, newcmd);
		command_check(shell, newcmd);	
	}
}

int	execbuiltin(t_minishell *shell, t_args *cmd)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (!ft_strcmp("cd", cmd->args[0]))
		ret = mini_cd(shell, cmd);
	else if (!ft_strcmp("unset", cmd->args[0]))
		ret = mini_unset(shell, "MAIL="); // change this
	else if (!ft_strcmp("exit", cmd->args[0]))
		mini_exit(shell);
	else if (!ft_strcmp("export", cmd->args[0]))
		ret = mini_export(shell, cmd);
	else if (!ft_strcmp("pwd", cmd->args[0]))
		ret = mini_pwd(shell);
	else if (!ft_strcmp("env", cmd->args[0]))
		ret = mini_env(shell);
	else if (!ft_strcmp("echo", cmd->args[0]))
		ret = mini_echo(cmd);
	return(ret);
}

int	scanifbuiltin(t_args *cmd)
{
	if (!ft_strcmp("cd", cmd->args[0]))
		return (1);
	else if (!ft_strcmp("unset", cmd->args[0]))
		return (1);
	else if (!ft_strcmp("exit", cmd->args[0]))
		return (1); 
	else if (!ft_strcmp("export", cmd->args[0]))
		return (1);
	else if (!ft_strcmp("pwd", cmd->args[0]))
		return (1);
	else if (!ft_strcmp("env", cmd->args[0]))
		return (1); 
	else if (!ft_strcmp("echo", cmd->args[0]))
		return (1);
	else
		return (0);
}

void	single_cmd(t_minishell *shell, t_args *cmd)
{
	pid_t	pid;
	int		status;

	if (handle_heredoc(cmd) == 1)
	{
		shell->exit_code = 2;
		return ;
	}
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

void	execute(t_minishell *shell)
{
	if (!shell->commands)
		return ;
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
