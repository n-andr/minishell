/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:53:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/26 17:18:44 by lde-taey         ###   ########.fr       */
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

/* 
this function
0. stores the current directory for later
1. checks if the argument is - or nothing (chdir treats '..', '/' 
and '~' automatically, so these are the only two special cases)
2. checks for relative paths and updates the arg with environmentals if needed
3. checks if the directory change was successful by checking the return value
4. if yes, it updates the environmental values
*/
int	mini_cd(t_minishell *shell)
{
	char	arg[100] = "~/projects/Circle_3";
	int		ret;
	char	lastdir[MAX_INPUT_SIZE];

	if (!getcwd(lastdir, sizeof(lastdir)))
		return (-1);
	if (!strcmp(arg, "-"))
		ret = chdir(shell->oldpwd);
	else if (!strcmp(arg, ""))
		ret = chdir(shell->home);
	else
	{
		check_relative_path(arg, shell);
		ret = chdir(arg);
	}
	if (ret != 0)
		return (-1); // TODO error handling with perror
	add_environmentals(shell, lastdir);
	return (0);
}
