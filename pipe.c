/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:29:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/31 15:00:55 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// file descriptors are [1] for write side and [0] for read side
void	child_process(int *pipe_fd, t_minishell *shell, t_args *command, int *in_fd)
{
	if (command->previous != NULL)
	{
		if (dup2(*in_fd, STDIN_FILENO) == -1)
			perror ("dup 1 failed");
		else
			close(*in_fd);
	}
	if (command->next != NULL)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror ("dup 2 failed");
		else
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
	// exit(0); // important to leave it commented out -- messes with pipes and system functions
}

int	ft_pipe(t_minishell *shell)
{
	int		pipe_fd[2];
	pid_t	child_pid;
	t_args	*temp;
	int		in_fd;
	int		status;

	in_fd = -1;
	temp = shell->commands;
	while (temp != NULL)
	{
		if (temp->next != NULL)
		{
			if (pipe(pipe_fd) == -1)
				return (0);
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("child process");
			return (2);
		}
		else if (child_pid == 0)
			child_process(pipe_fd, shell, temp, &in_fd);
		else
			parent_process(pipe_fd, &in_fd);
		temp = temp->next;
	}
	// free (temp);
	temp = shell->commands;
	while (temp != NULL)
	{
		waitpid(temp->childpid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status); // does it make sense to update this value in a loop?
		else
			shell->exit_code = EXIT_FAILURE;
		temp = temp->next;
	}
	return (1);
}
