/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:29:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/15 15:47:10 by lde-taey         ###   ########.fr       */
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
	// check for builtins here? special treatment of cd and exit?
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
	pid_t	child_pid; // use the value in the struct instead
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
		else
		{
			pipe_fd[0] = -1;
			pipe_fd[1] = -1;
		}
		child_pid = fork(); // store in struct
		if (child_pid == -1)
		{
			perror("child process");
			return (2);
		}
		if (child_pid == 0)
			child_process(pipe_fd, shell, temp, &in_fd);
		parent_process(pipe_fd, &in_fd);
		temp = temp->next;
	}
	// while (wait(NULL) > 0);
	while ((child_pid = waitpid(-1, &status, 0)) > 0)
	{
		if (WIFEXITED(status))
			shell->exit_code = WEXITSTATUS(status);
		else
			shell->exit_code = EXIT_FAILURE;
	}
	free (temp);
	return (1);
}
