/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:29:57 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/11 16:46:16 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// file descriptors are [1] for write side and [0] for read side
void	child_process(int *pipe_fd, t_minishell *shell, t_args *cmd, int *in_fd)
{
	if (cmd->previous != NULL)
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

	if (sh->commands->cmd_valid == false)
		return (-1);
	else
	{
		if (handle_heredoc(temp) == 1)
		{
			sh->exit_code = 2;
			return (3);
		}
		child_pid = fork();
		temp->childpid = child_pid;
		if (child_pid == -1)
		{
			perror("child process");
			return (4);
		}
		else if (child_pid == 0)
			child_process(pfd, sh, temp, in_fd);
		else
			parent_process(pfd, in_fd);
	}
	return (child_pid);
}

void	wait_for_children(t_minishell *shell, pid_t child_pid)
{
	t_args	*temp;
	int		status;

	temp = shell->commands;
	while (temp != NULL)
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status) && child_pid == temp->childpid)
			shell->exit_code = WEXITSTATUS(status);
		else
			shell->exit_code = EXIT_FAILURE;
		temp = temp->next;
	}
}

int	ft_pipe(t_minishell *shell)
{
	int		pipe_fd[2];
	pid_t	child_pid;
	t_args	*temp;
	int		in_fd;

	in_fd = -1;
	temp = shell->commands;
	child_signals();
	while (temp != NULL)
	{
		if (temp->next != NULL)
		{
			if (pipe(pipe_fd) == -1)
				return (2);
		}
		expand_command(shell, temp);
		child_pid = process_cmd(shell, temp, pipe_fd, &in_fd);
		temp = temp->next;
	}
	wait_for_children(shell, child_pid);
	return (0);
}
