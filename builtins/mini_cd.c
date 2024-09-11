/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:53:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/11 13:48:38 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_environmentals(t_minishell *shell, char *lastdir)
{
	char	newdir[MAX_INPUT_SIZE];

	free(shell->oldpwd);
	shell->oldpwd = ft_strdup(lastdir);
	if (getcwd(newdir, sizeof(newdir)))
	{
		free(shell->pwd);
		shell->pwd = ft_strdup(newdir);
	}
}

static void	check_relative_path(char *arg, t_minishell *shell)
{
	char	path[MAX_INPUT_SIZE];

	if (arg[0] == '~')
	{
		ft_strcpy(path, shell->home);
		ft_strcat(path, "/");
		ft_strcat(path, arg + 2);
		ft_strcpy(arg, path);
	}
}

static int change_directory(t_args *cmd, t_minishell *shell)
{
	int		ret;
	
	if (!ft_strcmp(cmd->args[1], "-"))
		ret = chdir(shell->oldpwd);
	else if (!strcmp(cmd->args[1], ""))
		ret = chdir(shell->home);
	else
	{
		check_relative_path(cmd->args[1], shell);
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

	if (cmd->args[2])
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
