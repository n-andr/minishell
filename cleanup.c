/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:40:56 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/14 17:23:55 by lde-taey         ###   ########.fr       */
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
	while (commands->args[i]) // free args
	{
		free (commands->args[i]);
		i ++;
	}
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

    while (shell->commands) {
        next = shell->commands->next;
		free_commands_args(shell->commands);
		free_commands_redir(shell->commands);
        free(shell->commands);
        shell->commands = next;
    }
}

void	free_everything(t_minishell *shell)
{
	free_array(shell->envs);
	free_commans(shell); //free shell->comands->args array & ree shell->comands->redir array
	free_commans(shell);
	free(shell->home);
	free(shell->pwd);
	free(shell->oldpwd);
	free_array(shell->paths);
	//free(shell->commands->args);
	//free_array(shell->commands->redir); // sth wrong here
	// free(shell->commands->args);
	// free_array(shell->commands->redir); // sth wrong here
	free(shell->commands);
}