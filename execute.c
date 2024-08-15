/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:23:44 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/15 15:40:31 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd(t_minishell *shell, t_args *command)
{
	char	*cmd;
	char	*tmp;
	char	*newcmd;
	int		i;

	check_redirections(command);
	i = 0;
	cmd = ft_strdup(command->args[0]);
	if (!access(cmd, F_OK))
		execve(cmd, command->args, shell->envs);
	else
	{
		while (shell->paths[i] != NULL)
		{
			tmp = ft_strjoin(shell->paths[i], "/");
			newcmd = ft_strjoin(tmp, cmd);
			if (!access(newcmd, F_OK))
				execve(newcmd, command->args, shell->envs);
			i++;
		}
	}
	perror("Could not execve");
	return (0);
}

static int	scanifbuiltin(t_minishell *shell)
{
	//printf("scanifbuildin: %s\n", shell->commands->args[0]); //delete
	// implement redirections
	if (!ft_strcmp("pwd", shell->commands->args[0]))
		return (mini_pwd(shell), 1);
	else if (!ft_strcmp("cd", shell->commands->args[0]))
		return (mini_cd(shell), 1);
	else if (!ft_strcmp("env", shell->commands->args[0]))
		return (mini_env(shell), 1);
	else if (!ft_strcmp("unset", shell->commands->args[0]))
		return (mini_unset(shell, "MAIL="), 1); // to be corrected
	else if (!ft_strcmp("echo", shell->commands->args[0]))
		return (mini_echo(shell), 1); // to be confirmed
	else if (!ft_strcmp("exit", shell->commands->args[0]))
		return (mini_exit(shell), 1); // to be confirmed
	else
		return (0);
}

int	single_cmd(t_minishell *shell)
{
	pid_t	pid;
	int		status;

	//printf("single_cmd: %s\n", shell->commands->args[0]); //delete
	if (scanifbuiltin(shell))
		return (1);
	// handle_heredoc(shell); // check where this should go
	pid = fork();
	if (pid < 0)
	{
		error_exec();
		return (0);
	}
	if (pid == 0)
		handle_cmd(shell, shell->commands);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	// do reset here
	return (1);
}

int	execute(t_minishell *shell)
{
	if (!shell->commands)
		return (0);
	if (shell->commands->is_pipe == 0)
	{
		single_cmd(shell);
		free_commans(shell);
		return (1);
	}
	else if (shell->commands->next)
		ft_pipe(shell); // what with builtins in the pipe?
	free_commans(shell);
	return (1);
}
