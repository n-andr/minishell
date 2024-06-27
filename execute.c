/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:23:44 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/27 16:35:51 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_cmd(t_minishell *shell)
{	
	char *temp;
	temp = (char *)&shell->arg;
	
	check_redirections(shell);
	if (execve(shell->cmd, &temp, shell->envs) == -1)
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
	
	ft_strcpy(shell->cmd, "cat");
	ft_strcpy(shell->arg, "free.c");

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