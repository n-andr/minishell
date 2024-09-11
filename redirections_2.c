/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:57:45 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/11 17:14:30 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_fds(t_minishell *shell)
{
	shell->fds->stdin = dup(STDIN_FILENO);
	shell->fds->stdout = dup(STDOUT_FILENO);
}

void	reset_fds(t_minishell *shell)
{
	dup2(shell->fds->stdin, STDIN_FILENO);
	dup2(shell->fds->stdout, STDOUT_FILENO);
	close(shell->fds->stdin);
	close(shell->fds->stdout);
}

int	check_redirections(t_args *command)
{
	int	ret;

	if (!command->redir)
		return (EXIT_SUCCESS);
	ret = redirection_loop(command);
	return (ret);
}
