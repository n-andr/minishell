/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:40:56 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/04 16:13:22 by nandreev         ###   ########.fr       */
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
void	free_commans(t_minishell *shell)
{
	t_args *next;

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
	free(shell->args);
	free(shell->cmd);
	free(shell->home);
	free(shell->pwd);
	free(shell->oldpwd);
}