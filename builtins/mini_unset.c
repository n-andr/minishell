/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:20:49 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/10 17:22:54 by lde-taey         ###   ########.fr       */
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
		if (!ft_strncmp(envs[i], str, ft_strlen(str)))
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

int	check_if_valid(t_args *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1][1] == '\0')
		return (EXIT_FAILURE);
	if (where_is_equalsign(cmd->args[1]) > 0)
		return (EXIT_FAILURE);
	while (cmd->args[1][i] != '\0')
	{
		if (cmd->args[1][i] == '/')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	mini_unset(t_minishell *shell, t_args *cmd)
{
	if (cmd->args[1] == NULL || cmd->args[2])
		return (EXIT_SUCCESS);
	if (check_if_valid(cmd) == 1)
		return (EXIT_SUCCESS);
	delete_var(shell->envs, cmd->args[1]);
	// mini_env(shell); // test
	return (EXIT_SUCCESS);
}
