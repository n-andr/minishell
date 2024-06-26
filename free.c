/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:39:56 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/25 22:40:57 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_minishell *shell)
{
	int i;

	i = 0;
	while (shell->args[i]) // free args
	{
		free (shell->args[i]);
		i ++;
	}
	shell->args = NULL;
}