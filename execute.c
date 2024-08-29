/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:23:44 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/02 20:35:56 by nandreev         ###   ########.fr       */
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

	//expand_command and check if valid
	check_redirections(command);
	if (scanifbuiltin(command) == 1)
	{
		execbuiltin(shell, command);
		exit(EXIT_SUCCESS);
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
				// printf("we are here\n");
				execve(newcmd, command->args, shell->envs);
			i++;
			//free stuff
		}
	}
	perror("Could not execve");
	return (0);
}

void	execbuiltin(t_minishell *shell, t_args *cmd)
{
	if (!ft_strcmp("cd", cmd->args[0]))
		mini_cd(shell, cmd);
	else if (!ft_strcmp("unset", cmd->args[0]))
		mini_unset(shell, "MAIL=");
	else if (!ft_strcmp("exit", cmd->args[0]))
		mini_exit(shell); // to be confirmed
	else if (!ft_strcmp("export", cmd->args[0]))
		(mini_export(shell, cmd)); // TODO
	else if (!ft_strcmp("pwd", cmd->args[0]))
		mini_pwd(shell);
	else if (!ft_strcmp("env", cmd->args[0]))
		mini_env(shell);
	else if (!ft_strcmp("echo", cmd->args[0]))
		mini_echo(cmd); // to be confirmed
	else
		return ;
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

int	single_cmd(t_minishell *shell, t_args *cmd)
{
	pid_t	pid;
	int		status;

	if (scanifbuiltin(cmd) == 1)
	{
		execbuiltin(shell, cmd);
		return (1); // return exit_status? // shell->exit_code = execbuiltin(shell);
	}
	// handle_heredoc(shell);
	pid = fork();
	if (pid < 0)
	{
		error_exec();
		return (0);
	}
	if (pid == 0)
		handle_cmd(shell, cmd);
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
		single_cmd(shell, shell->commands);
		free_commans(shell);
		return (0);//  maybe return exit-code
	}
	else if (shell->commands->next)
		ft_pipe(shell);
	free_commans(shell);
	return (0);
}
