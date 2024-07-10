/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:29:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/10 16:38:28 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// file descriptors are [1] for write side and [0] for read side
void	handle_leftside(int *pipe_fd, t_minishell *shell, t_args *command)
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	handle_cmd(shell, command);
}

void	handle_rightside(int *pipe_fd, t_minishell *shell, t_args *command)
{
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	// close(pipe_fd[1]);
	handle_cmd(shell, command);
}

int	ft_pipe(t_minishell *shell, t_args *command)
{
	int		pipe_fd[2];
	pid_t 	child_pid;
	int		status;

	if (pipe(pipe_fd) < 0)
		return (0);
	child_pid = fork();
	if (child_pid < 0)
		return (2);
	if (child_pid == 0)
		handle_leftside(pipe_fd, shell, command);
	close(pipe_fd[1]);
	if (command + 1 != NULL) // adapt to linked list
		handle_rightside(pipe_fd, shell, command + 1);
	close(pipe_fd[0]);
	waitpid(child_pid, &status, 0);
	return (1);
}