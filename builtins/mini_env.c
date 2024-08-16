/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:07:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/16 15:59:47 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_env(t_minishell *shell)
{
	int i;

	i = 0;
	while (shell->envs[i] != NULL)
	{
		printf("%s\n", shell->envs[i]); // replace with write and fd for pipes
		i++;
	}
	return (0);
}
