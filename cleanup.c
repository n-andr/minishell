/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:40:56 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/11 12:54:04 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
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
	int i;

	i = 0;
	if (commands->args == NULL)
		return ;
	while (commands->args[i]) // free args
	{
		free (commands->args[i]);
		i ++;
	}
	free(commands->args);
	commands->args = NULL;
}

void	free_commands_redir(t_args *commands)
{
	int i;

	i = 0;
	if (commands->redir) 
	{
		i = 0;
		while (commands->redir[i]) {
			free(commands->redir[i]);
			i++;
		}
		free(commands->redir);
		commands->redir = NULL;
	}
}

void	free_commands(t_minishell *shell)
{
	t_args *next;
	//check previous command to start freeing from the begininning

    while (shell->commands) {
        next = shell->commands->next;
		free_commands_args(shell->commands);
		free_commands_redir(shell->commands);
		shell->pid = 0; // check again
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
	free_commands(shell); //free shell->comands->args array & free shell->comands->redir array
	free(shell->home);
	free(shell->pwd);
	free(shell->oldpwd);
	free_array(shell->paths);
	free(shell->commands);
	free(shell->fds);
	rl_clear_history();// tbh not sure if this is necessary
}