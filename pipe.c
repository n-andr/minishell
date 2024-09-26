/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:29:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/26 15:42:48 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// file descriptors are [1] for write side and [0] for read side
void	child_process(int *pipe_fd, t_minishell *shell, t_args *cmd, int *in_fd)
{
	signal_config_children();
	if (cmd->previous != NULL && cmd->previous->cmd_valid == true)
	{
		if (dup2(*in_fd, STDIN_FILENO) == -1)
			perror ("dup 1 failed");
		else
			close(*in_fd);
	}
	if (cmd->next != NULL)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror ("dup 2 failed");
		else
			close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
	handle_cmd(shell, cmd);
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

pid_t	process_cmd(t_minishell *sh, t_args *temp, int pfd[2], int *in_fd)
{
	pid_t	child_pid;

	if (handle_heredoc(temp, sh) == 1)
	{
		sh->exit_code = 2;
		return (33);
	}
	child_pid = fork();
	temp->childpid = child_pid;
	if (child_pid == -1)
	{
		perror("child process");
		return (34);
	}
	else if (child_pid == 0)
		child_process(pfd, sh, temp, in_fd);
	else
		parent_process(pfd, in_fd);
	return (child_pid);
}

void	wait_for_children(t_minishell *shell, int counter, pid_t child_pid)
{
	int		status;
	int		i;

	signal_config_children();
	i = 0;
	while (i < counter)
	{
		status = 0;
		waitpid(shell->pid[i], &status, 0); 
		if (WIFEXITED(status) && child_pid == shell->pid[i])
			shell->exit_code = WEXITSTATUS(status);
		else
			shell->exit_code = EXIT_FAILURE;
		i++;
	}
}

int	ft_pipe(t_minishell *shell)
{
	int		pipe_fd[2];
	t_args	*temp;
	int		in_fd;
	int		counter;

	in_fd = -1;
	counter = 0;
	temp = shell->commands;
	while (temp != NULL)
	{
		if (temp->next != NULL)
		{
			if (pipe(pipe_fd) == -1)
				return (2);
		}
		expand_command(shell, temp);
		if (temp->cmd_valid == true)
			shell->pid[counter] = process_cmd(shell, temp, pipe_fd, &in_fd);
		else
			shell->pid[counter] = -1;
		temp = temp->next;
		counter++;
	}
	wait_for_children(shell, counter, shell->pid[counter - 1]);
	return (0);
}
