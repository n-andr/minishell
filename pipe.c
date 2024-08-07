/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:29:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/07 13:57:05 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// file descriptors are [1] for write side and [0] for read side
// file descriptors are inherited so we have to manage (and close) the fds in each of the processes
void	handle_leftside(int *pipe_fd, t_minishell *shell, t_args *command)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	handle_cmd(shell, command);
	exit(1);
}

void	handle_rightside(int *pipe_fd, t_minishell *shell, t_args *command)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	handle_cmd(shell, command);
	exit(1);
}

int	ft_pipe(t_minishell *shell, t_args *command, int i)
{
	int		pipe_fd[2];
	pid_t 	child_pid;
	int		status;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	i += 0; // delete later
	child_pid = fork(); // copies the fds
	if (child_pid == -1)
	{
		perror("child process");
		return (2);
	}
	if (child_pid == 0)
		handle_leftside(pipe_fd, shell, command);
	else
		handle_rightside(pipe_fd, shell, command + 1);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(child_pid, &status, 0);
	return (1);
}
