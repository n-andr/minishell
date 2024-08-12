/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:29:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/12 15:14:06 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// file descriptors are [1] for write side and [0] for read side
void	child_process(int *pipe_fd, t_minishell *shell, t_args *command, int *in_fd)
{
	if (*in_fd != -1)
	{
		dup2(*in_fd, STDIN_FILENO);
		close(*in_fd);
	}
	if (pipe_fd[1] != -1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
	handle_cmd(shell, command);
	exit(0);
}

void	parent_process(int *pipe_fd, int *in_fd)
{
	if (*in_fd != -1)
		close (*in_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	*in_fd = pipe_fd[0];
}

int	ft_pipe(t_minishell *shell) 
{
	int		pipe_fd[2];
	pid_t	child_pid;
	t_args	*temp;
	int		in_fd;
	
	in_fd = -1;
	temp = shell->commands;
	while (temp != NULL) // adapt to linked lists
	{
		if (temp->next != NULL) // adapt to linked lists
		{
			if (pipe(pipe_fd) == -1)
				return (0);
		}
		else
		{
			pipe_fd[0] = -1;
			pipe_fd[1] = -1;
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("child process");
			return (2);
		}
		if (child_pid == 0)
			child_process(pipe_fd, shell, shell->commands, &in_fd);
		parent_process(pipe_fd, &in_fd);
		shell->commands = shell->commands->next;
	}
	while (wait(NULL) > 0);
	return (1);
}
