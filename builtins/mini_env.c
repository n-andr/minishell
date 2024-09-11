/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:07:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/11 14:03:50 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_env(t_minishell *shell, t_args *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1])
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	while (shell->envs[i] != NULL)
	{
		ft_putstr_fd(shell->envs[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	return (0);
}
