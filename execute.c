/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:23:44 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/26 17:17:54 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execute(char *str, t_minishell *shell) // change according to way args are parsed into structs
{
	// pid_t	pid;
	// int		status;
	
	/*
	1. check if arguments are empty
	2. if built-in commands
		handle these in the parent process */
	if (scanifbuiltin(str, shell))
		return ;
	/* 
	3. external commands
		use a fork to create child processes and execvp the commands there
	
	pid = fork();
	if (pid == 0) // child process
	{
		
		execvp(data->cmd, data); // delete this eventually, is superfluous
		if (execvp(data->cmd, data) == -1)
			error_exec();
	}
	else if (pid < 0) // error
		error_exec();
	else // parent process
		waitpid(pid, &status, 0);
	
	4. expand functionality by handling redirections, pipes, improving
	error handling and heredocs
	*/
}