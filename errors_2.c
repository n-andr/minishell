/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:22:24 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/05 16:34:23 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stop_exec(t_minishell *shell, t_args *cmd)
{
	if(!shell->paths)
		exit(127);
	/* if(S_ISDIR(s.st_mode))
	{
		ft_putstr_fd("No such file or directory", STDERR_FILENO);
		free_everything(shell);
		exit(126);
	} */
	if (access(cmd->args[0], F_OK) == -1)
	{
		ft_putstr_fd("No such file or directory\n", STDERR_FILENO);
		free_everything(shell);
		exit(127);
	}
	else
	{
		ft_putstr_fd("Permission denied\n", STDERR_FILENO);
		free_everything(shell);
		exit(126);
	}
	
}