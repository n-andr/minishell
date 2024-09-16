/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:02:54 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/17 00:02:17 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_or_path(char *str)
{
	char	*builtins[8];
	int		i;

	if (str == NULL)
		return (0);
	builtins[0] = "cd";
	builtins[1] = "exit";
	builtins[2] = "echo";
	builtins[3] = "pwd";
	builtins[4] = "export";
	builtins[5] = "unset";
	builtins[6] = "env";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(str, builtins[i]) == 0)
			return (1);
		i ++;
	}
	if (ft_strchr(str, '/'))
		return (1);
	else
		return (0);
	return (0);
}

static void	free_tmp(char *tmp, char *newcmd)
{
	free(tmp);
	free(newcmd);
}

int	is_executable(t_minishell *shell, char *str)
{
	char	*tmp;
	char	*newcmd;
	int		i;

	if (str == NULL || ft_strlen(str) == 0)
		return (0);
	if (access(str, X_OK) == 0)
		return (1);
	else
	{
		i = 0;
		while (shell->paths[i] != NULL)
		{
			tmp = ft_strjoin(shell->paths[i], "/");
			newcmd = ft_strjoin(tmp, str);
			if (access(newcmd, X_OK) == 0)
			{
				free_tmp(tmp, newcmd);
				return (1);
			}
			i++;
			free_tmp(tmp, newcmd);
		}
	}
	return (0);
}

void	exit_code(t_minishell *shell, t_args *cmd, int code, bool is_valid)
{
	if (cmd->next == NULL)
	{
		shell->exit_code = code;
	}
	cmd->cmd_valid = is_valid;
	return ;
}

void	check_if_cmd_valid(t_minishell *shell, t_args *cmd)
{
	if (cmd == NULL)
		exit_code(shell, cmd, 0, false);
	if ((cmd->args == NULL || cmd->args[0] == NULL )
		&& cmd->is_redir == 0 && cmd->is_pipe == 0)
		exit_code(shell, cmd, 0, false);
	else if (cmd->args == NULL && cmd->is_redir == 0 && cmd->is_pipe != 0)
	{
		exit_code(shell, cmd, 0, false);
	}
	else if ((cmd->args != NULL && (is_builtin_or_path(cmd->args[0])
				|| is_executable(shell, cmd->args[0])))
		|| (cmd->is_redir == 1 && cmd->args == NULL))
		exit_code(shell, cmd, 0, true);
	else
	{
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": command not found\n", 20);
		exit_code(shell, cmd, 127, false);
	}
	return ;
}
