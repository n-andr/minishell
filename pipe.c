/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:29:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/05 15:31:18 by nandreev         ###   ########.fr       */
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
	close(pipe_fd[1]);
	handle_cmd(shell, command);
}

int	ft_pipe(t_minishell *shell, t_args *command, int i)
{
	int		pipe_fd[2];
	pid_t 	child_pid;
	int		status;

	if (pipe(pipe_fd) < 0)
		return (0);
	i += 0; 
	// printf("\n%s\n", command->args[1]);
	// printf("\n%s\n\n", &shell->commands[i + 1].args[0][0]);
	child_pid = fork();
	if (child_pid < 0)
		return (2);
	if (child_pid == 0)
	{
		// printf("left ok\n");
		handle_leftside(pipe_fd, shell, command);
	}
	if (command->next != NULL)
	// adapt to linked list
	{
		// printf("right ok\n");
		handle_rightside(pipe_fd, shell, command + 1);
	}
	waitpid(child_pid, &status, 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (1);
}
