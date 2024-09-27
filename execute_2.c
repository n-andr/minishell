/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:22:49 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/27 17:28:02 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execbuiltin(t_minishell *shell, t_args *cmd)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if (!ft_strcmp("cd", cmd->args[0]))
		ret = mini_cd(shell, cmd);
	else if (!ft_strcmp("unset", cmd->args[0]))
		ret = mini_unset(shell, cmd);
	else if (!ft_strcmp("exit", cmd->args[0]))
		mini_exit(shell);
	else if (!ft_strcmp("export", cmd->args[0]))
		ret = mini_export(shell, cmd);
	else if (!ft_strcmp("pwd", cmd->args[0]))
		ret = mini_pwd(shell);
	else if (!ft_strcmp("env", cmd->args[0]))
		ret = mini_env(shell, cmd);
	else if (!ft_strcmp("echo", cmd->args[0]))
		ret = mini_echo(cmd);
	return (ret);
}

int	scanifbuiltin(t_args *cmd)
{
	if (!ft_strcmp("cd", cmd->args[0]))
		return (1);
	else if (!ft_strcmp("unset", cmd->args[0]))
		return (1);
	else if (!ft_strcmp("exit", cmd->args[0]))
		return (1); 
	else if (!ft_strcmp("export", cmd->args[0]))
		return (1);
	else if (!ft_strcmp("pwd", cmd->args[0]))
		return (1);
	else if (!ft_strcmp("env", cmd->args[0]))
		return (1); 
	else if (!ft_strcmp("echo", cmd->args[0]))
		return (1);
	else
		return (0);
}
