/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:39:23 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/26 14:15:11 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_paths(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->envs[i] != NULL)
	{
		if (!ft_strncmp(shell->envs[i], "PATH=", 5))
		{
			if(shell->paths != NULL)
			{
				free_array(shell->paths);
				shell->paths = NULL;
			}
			shell->paths = ft_split(shell->envs[i] + 5, ':');
		}
		i++;
	}
}

void	store_pwd(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->envs[i] != NULL)
	{
		if (!ft_strncmp(shell->envs[i], "PWD=", 4))
		{
			shell->pwd = ft_strdup(shell->envs[i] + 4);
			if (!shell->pwd)
				malloc_error(shell);
		}
		else if (!ft_strncmp(shell->envs[i], "OLDPWD=", 7))
		{
			shell->oldpwd = ft_strdup(shell->envs[i] + 7);
			if (!shell->oldpwd)
				malloc_error(shell);
		}
		else if (!ft_strncmp(shell->envs[i], "HOME=", 5))
		{
			shell->home = ft_strdup(shell->envs[i] + 5);
			if (!shell->home)
				malloc_error(shell);
		}
		i++;
	}
}

void	create_env_array(char **env, t_minishell *shell)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	shell->envs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!shell->envs)
		malloc_error(shell);
	i = 0;
	while (env[i] != NULL)
	{
		shell->envs[i] = ft_strdup(env[i]);
		if (!shell->envs[i])
		{
			while (i > 0)
				free(shell->envs[i - 1]);
			free(shell->envs);
			malloc_error(shell);
		}
		i++;
	}
	shell->envs[i] = NULL;
}

// When the program starts running, this function copies the environmental 
// values into a struct
void	init_environmentals(char **env, t_minishell *shell)
{
	create_env_array(env, shell);
	store_pwd(shell);
	create_paths(shell);
	shell->fds = malloc(sizeof(t_storefd));
	if (!shell->fds)
		malloc_error(shell);
}
