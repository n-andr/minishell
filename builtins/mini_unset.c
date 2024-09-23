/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:20:49 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/23 15:25:24 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	where_is_equalsign(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (-1);
}

void	delete_var(char **envs, char *str)
{
	int	i;

	i = 0;
	while (envs[i] != NULL)
	{
		if (!ft_strncmp(envs[i], str, (where_is_equalsign(envs[i]) - 1)))
		{
			free(envs[i]);
			while (envs[i + 1])
			{
				envs[i] = envs[i + 1];
				i++;
			}
			envs[i] = NULL;
			return ;
		}
		i++;
	}
}

int	check_if_valid(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '\0')
		return (EXIT_FAILURE);
	if (where_is_equalsign(arg) > 0)
		return (EXIT_FAILURE);
	while (arg[i] != '\0')
	{
		if (arg[i] == '/')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	mini_unset(t_minishell *shell, t_args *cmd)
{
	int	i;

	if (cmd->args[1] == NULL)
		return (EXIT_SUCCESS);
	i = 1;
	while (cmd->args[i] != NULL)
	{
		if (check_if_valid(cmd->args[i]) == 0)
		{
			delete_var(shell->envs, cmd->args[i]);
			if (ft_strcmp(cmd->args[i], "PATH") == 0)
			{
				free_array(shell->paths);
				shell->paths = NULL;
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
