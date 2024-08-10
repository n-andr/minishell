/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:29:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/10 11:45:41 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// file descriptors are [1] for write side and [0] for read side
void	child_process(int *pipe_fd, t_minishell *shell, t_args *command, int *in_fd)
{
	if (*in_fd != -1) // for every pipe that is not the first
	{
        dup2(*in_fd, STDIN_FILENO);
        close(*in_fd);
    }
	if (pipe_fd[1] != -1) // for every pipe that is not the last
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

int	ft_pipe(t_minishell *shell) //, t_args *command)
{
	int		pipe_fd[2];
	pid_t 	child_pid;
	int		in_fd;
	int		i;

	in_fd = -1;
	i = 0;
	while (shell->commands[i].args[0] != NULL) // adapt to linked lists
	{
		printf("%ix \n\n", i + 1);
		printf("These are the arguments: %s and %s\n\n\n", shell->commands[i].args[0], shell->commands[i].args[1]);
		if (shell->commands[i + 1].args[0] != NULL) // adapt to linked lists
		{
			if(pipe(pipe_fd) == -1)
				return (0);
		}
		else
		{
			pipe_fd[0] = -1;
			pipe_fd[1] = -1;
		}
		child_pid = fork(); // copies the fds
		if (child_pid == -1)
		{
			perror("child process");
			return (2);
		}
		if (child_pid == 0)
			child_process(pipe_fd, shell, &shell->commands[i], &in_fd);
		parent_process(pipe_fd, &in_fd);
		i++;
	}
	while (wait(NULL) > 0);
	return (1);
}
