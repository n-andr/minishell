/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:23:44 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/28 16:30:54 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_cmd(t_minishell *shell)
{	
	check_redirections(shell);
	if (execve(shell->cmd[0], shell->args, shell->envs) == -1)
		perror("Could not execve");
}

static int	scanifbuiltin(char *str, t_minishell *shell)
{
	if(!ft_strcmp("pwd", str))
		return (mini_pwd(shell), 1);
	else if(!ft_strcmp("cd", str))
		return (mini_cd(shell), 1);
	else if(!ft_strcmp("env", str))
		return (mini_env(shell), 1);
	else if(!ft_strcmp("unset", str))
		return (mini_unset(shell, "MAIL="), 1);
//	else if(!ft_strcmp("echo", str))
//		return (mini_echo(data), 1);
	else
		return (0);
}

int	execute(char *str, t_minishell *shell) // change according to way args are parsed into structs
{
	pid_t	pid;
	int		status;
	
	shell->cmd = (char **)malloc((2 * sizeof(char*)));
	shell->args = (char **)malloc((3 * sizeof(char*)));
	shell->cmd[0] = "/usr/bin/cat";
	shell->cmd[1] = NULL;
	shell->args[0] = "cat"; // command should be included in the args!
	shell->args[1] = "free.c";
	shell->args[2] = NULL;

	/*
	0. check if arguments are empty
	1. call expander (?)
	2. if built-in commands
		handle these in the parent process */
	if (scanifbuiltin(str, shell))
		return (1);
	/* 
	3. external commands
	check heredoc?
	use a fork to create child processes and execvp the commands there */
	pid = fork();
	if (pid < 0)
	{
		error_exec();
		return (0);
	}
	if (pid == 0)
		handle_cmd(shell);
	else // else necessary?
		waitpid(pid, &status, 0);
	/* 4. expand functionality by handling redirections, improving
	error handling and heredocs
	*/
	return (1);
}