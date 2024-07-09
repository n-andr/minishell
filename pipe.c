/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:29:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/09 15:48:23 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_leftside(int *pipe_fd, t_minishell *shell, t_args *command)
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	handle_cmd(shell, command);
}

void	handle_rightside(int *pipe_fd, t_minishell *shell, t_args *command)
{
	dup2(pipe_fd[0], STDIN_FILENO); // file descriptors are [1] for read side and [0] for write side
	close(pipe_fd[0]);
	handle_cmd(shell, command);
}

// i do think somewhere a function needs to be executed? lol
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
	else
		return (0);
	handle_rightside(pipe_fd, shell, command->next);
	close(pipe_fd[0]); // you also have to close them in the parent process
	close(pipe_fd[1]);
	waitpid(child_pid, &status, 0);
	return (1);
}