/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:22:24 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/10 12:59:17 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	directory_check(t_minishell *shell, char *cmd)
{
	struct stat st;
	
	if(stat(cmd, &st) == -1)
		return ;
	if(S_ISDIR(st.st_mode))
	{
		ft_putstr_fd(" Is a directory\n", STDERR_FILENO);
		free_everything(shell);
		exit(126);
	}
}

void	command_check(t_minishell *shell, char *cmd)
{
	if(!shell->paths)
		exit(127);
	if (access(cmd, F_OK) == -1)
	{
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		free_everything(shell);
		exit(127);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
		free_everything(shell);
		exit(126);
	}
}