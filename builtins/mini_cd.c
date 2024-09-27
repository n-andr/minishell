/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:53:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/27 18:32:45 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_minishell *shell, char *env, char *newinfo)
{
	int	i;
	int	len;

	i = 0;
	while (shell->envs[i] != NULL)
	{
		if (!ft_strncmp(shell->envs[i], env, ft_strlen(env)))
		{
			free(shell->envs[i]);
			len = ft_strlen(env) + 1 + ft_strlen(newinfo) + 1;
			shell->envs[i] = (char *)malloc(len * sizeof(char *));
			ft_strcpy(shell->envs[i], env);
			ft_strcat(shell->envs[i], "=");
			ft_strcat(shell->envs[i], newinfo);
			shell->envs[i][len] = '\0';
			break ;
		}
		i++;
	}
}

static void	add_environmentals(t_minishell *shell, char *lastdir)
{
	char	newdir[MAX_INPUT_SIZE];

	free(shell->oldpwd);
	shell->oldpwd = ft_strdup(lastdir);
	update_env(shell, "OLDPWD", lastdir);
	if (getcwd(newdir, sizeof(newdir)))
	{
		free(shell->pwd);
		shell->pwd = ft_strdup(newdir);
	}
	update_env(shell, "PWD", shell->pwd);
}

static void	check_relative_path(char **arg, t_minishell *shell)
{
	char	path[MAX_INPUT_SIZE];
	char	*temp;

	if ((*arg)[0] == '~' && (*arg)[1] == '/')
	{
		ft_strcpy(path, shell->home);
		ft_strcat(path, "/");
		ft_strcat(path, *arg + 2);
		temp = ft_strdup(path);
		if (temp)
		{
			free(*arg);
			*arg = temp;
		}
	}
}

static int	change_directory(t_args *cmd, t_minishell *shell)
{
	int		ret;

	if (!cmd->args[1] || cmd->args[1][0] == '\0')
		ret = chdir(shell->home);
	else if (!ft_strcmp(cmd->args[1], "-"))
		ret = chdir(shell->oldpwd);
	else if (!ft_strcmp(cmd->args[1], "~"))
		ret = chdir(shell->home);
	else
	{
		check_relative_path(&cmd->args[1], shell);
		ret = chdir(cmd->args[1]);
	}
	if (ret != 0)
	{
		perror ("cd");
		shell->exit_code = 1;
		return (1);
	}
	return (0);
}

/* 
this function
0. stores the current directory for later
1. checks if the argument is - or nothing (chdir treats '..', '/' 
and '~' automatically, so these are the only two special cases)
2. checks for relative paths and updates the arg with environmentals if needed
3. checks if the directory change was successful by checking the return value
4. if yes, it updates the environmental values
*/
int	mini_cd(t_minishell *shell, t_args *cmd)
{
	char	lastdir[MAX_INPUT_SIZE];

	if (cmd->args[1] != NULL && cmd->args[2])
	{
		too_many_args_error();
		shell->exit_code = 1;
		return (1);
	}
	if (!getcwd(lastdir, sizeof(lastdir)))
	{
		shell->exit_code = 1;
		return (1);
	}
	if (change_directory(cmd, shell) == EXIT_FAILURE)
		return (1);
	add_environmentals(shell, lastdir);
	return (0);
}
