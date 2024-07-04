/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:05:24 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/04 13:17:43 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int generate_heredoc(char *delimiter)
{
	generate_filename();
	// read line by line
	// stop when the delimiter is encountered
}

int	handle_heredoc(t_minishell *shell)
{
	int	i;
	
	i = 0;
	while (shell->redir[i] != NULL)
	{
		if (!ft_strcmp(shell->redir[i], "<<"))
			generate_heredoc(shell->redir[i + 1]);
		i++;
	}
}