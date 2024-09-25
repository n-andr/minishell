/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:40:56 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/25 11:37:45 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_commands_args(t_args *commands)
{
	int	i;

	i = 0;
	if (commands->args == NULL)
		return ;
	while (commands->args[i])
	{
		free (commands->args[i]);
		i ++;
	}
	free(commands->args);
	commands->args = NULL;
}

void	free_commands_redir(t_args *commands)
{
	int	i;

	i = 0;
	if (commands->redir) 
	{
		i = 0;
		while (commands->redir[i])
		{
			free(commands->redir[i]);
			i++;
		}
		free(commands->redir);
		commands->redir = NULL;
	}
}

void	free_commands(t_minishell *shell)
{
	t_args	*next;

	while (shell->commands) 
	{
		next = shell->commands->next;
		g_sigint_received = 0;
		free_commands_args(shell->commands);
		free_commands_redir(shell->commands);
		if (shell->commands->heredoc != NULL)
		{
			if (unlink(shell->commands->heredoc) < 0)
				perror("unlink");
			free(shell->commands->heredoc);
			shell->commands->heredoc = NULL;
		}
		free(shell->commands);
		shell->commands = next;
	}
}

void	free_everything(t_minishell *shell)
{
	free_array(shell->envs);
	free_commands(shell);
	if (shell->home)
		free(shell->home);
	if (shell->pwd)
		free(shell->pwd);
	if (shell->oldpwd)
		free(shell->oldpwd);
	free_array(shell->paths);
	free(shell->commands);
	if (shell->fds)
		free(shell->fds);
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->orig_termios);
}
