/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:40:56 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/03 01:45:17 by nandreev         ###   ########.fr       */
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

void	free_commans(t_minishell *shell)
{
	t_args *next;
	//check previous command to start freeing from the begininning

    while (shell->commands) {
        next = shell->commands->next;
		free_commands_args(shell->commands);
		free_commands_redir(shell->commands);
        free(shell->commands);
		shell->pid = 0; // check again
        shell->commands = next;
    }
}

void	free_everything(t_minishell *shell)
{
	free_array(shell->envs);
	free_commans(shell); //free shell->comands->args array & ree shell->comands->redir array
	free(shell->home);
	free(shell->pwd);
	free(shell->oldpwd);
	free_array(shell->paths);
	free(shell->commands);
	free(shell->fds);
}