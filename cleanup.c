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

    while (shell->commands) {
        next = shell->commands->next;
		//free args
		//free redir
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