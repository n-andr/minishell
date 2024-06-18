/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:23:44 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/18 16:20:55 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_data *data) // change according to way args are parsed into structs
{
	pid_t	pid;
	int		status;
	
	/*
	1. check if arguments are empty
	2. if built-in commands
		handle these in the parent process
	3. external commands
		use a fork to create child processes and execvp the commands there
	*/
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
	/* 
	4. expand functionality by handling redirections, pipes, improving
	error handling and heredocs
	*/
}