/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:23:44 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/23 14:30:21 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd(t_minishell *shell, t_args *command)
{
	char	*cmd;
	char	*tmp;
	char	*newcmd;
	int		i;
	// int		exit_code;

	check_redirections(command);
	if (scanifbuiltin_for_redir(shell))
	{
		if (shell->cmd_done == 1)
			exit(EXIT_SUCCESS); // check exit_code
	}
	cmd = ft_strdup(command->args[0]);
	i = 0;
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

int	scanifbuiltin_for_redir(t_minishell *shell)
{
	//printf("scanifbuildin: %s\n", shell->commands->args[0]); //delete
	if (!ft_strcmp("pwd", shell->commands->args[0]))
		return (mini_pwd(shell), 1);
	else if (!ft_strcmp("env", shell->commands->args[0]))
		return (mini_env(shell), 1);
	else if (!ft_strcmp("echo", shell->commands->args[0]))
		return (mini_echo(shell), 1); // to be confirmed
	else
		return (0);
}

int	scanifbuiltin_no_redir(t_minishell *shell)
{
	if (!ft_strcmp("cd", shell->commands->args[0]))
		return (mini_cd(shell), 1);
	else if (!ft_strcmp("unset", shell->commands->args[0]))
		return (mini_unset(shell, "MAIL="), 1); // to be corrected
	else if (!ft_strcmp("exit", shell->commands->args[0]))
		return (mini_exit(shell), 1); // to be confirmed
	// else if (!ft_strcmp("export", shell->commands->args[0]))
	//	return (mini_export(shell), 1); // TODO
	else
		return (0);
}

int	single_cmd(t_minishell *shell)
{
	pid_t	pid;
	int		status;

	//printf("single_cmd: %s\n", shell->commands->args[0]); //delete
	if (scanifbuiltin_no_redir(shell))
		return (1); // return exit_status?
	// handle_heredoc(shell);
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
	else
		shell->exit_code = EXIT_FAILURE;
	return (1);
}

int	execute(t_minishell *shell)
{
	// shell->fd_in = STDIN_FILENO; // check if this is necessary for redirections
	if (!shell->commands)
		return (0);
	signal(SIGINT, child_signals);
	if (shell->commands->is_pipe == 0)
	{
		single_cmd(shell);
		free_commans(shell);
		return (0);//  maybe return exit-code
	}
	else if (shell->commands->next)
		ft_pipe(shell);
	free_commans(shell);
	return (0);
}
