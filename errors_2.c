/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:22:24 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/16 21:49:15 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	directory_check(t_minishell *shell, char *cmd)
{
	struct stat	st;

	if (stat(cmd, &st) == -1)
		return ;
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (S_ISDIR(st.st_mode))
		{
			ft_putstr_fd(" Is a directory\n", STDERR_FILENO);
			free_everything(shell);
			exit(126);
		}
	}
}

void	command_check(t_minishell *shell, char *cmd)
{
	if (cmd[0] != '/' && (cmd[0] != '.' && cmd[1] != '/'))
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	if (!shell->paths)
		exit(127);
	if (access(cmd, F_OK) == -1)
	{
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
		free(cmd);
		free_everything(shell);
		exit(127);
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(" Permission denied\n", STDERR_FILENO);
		free(cmd);
		free_everything(shell);
		exit(126);
	}
}

int	pipe_error(void)
{
	ft_putendl_fd("minishell: syntax error near unexpected token `|'", STDERR_FILENO);
	return (-1);
}
