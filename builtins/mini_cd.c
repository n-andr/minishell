/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:53:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/21 16:52:01 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_environmentals(t_data *data, char *lastdir)
{
	char	newdir[MAX_INPUT_SIZE];
	
	free(data->oldpwd);
	data->oldpwd = ft_strdup(lastdir);
	if (getcwd(newdir, sizeof(newdir)))
	{
		free(data->pwd);
		data->pwd = ft_strdup(newdir);
	}
}

static void	check_relative_path(char *arg, t_data *data)
{
	char	path[MAX_INPUT_SIZE];

	if (arg[0] == '~')
	{
		ft_strcpy(path, data->home);
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
int	mini_cd(t_data *data)
{
	char	arg[100] = "~/projects/Circle_3";
	int		ret;
	char	lastdir[MAX_INPUT_SIZE];

	if (!getcwd(lastdir, sizeof(lastdir)))
		return (-1);
	if (!strcmp(arg, "-"))
		ret = chdir(data->oldpwd);
	else if (!strcmp(arg, ""))
		ret = chdir(data->home);
	else
	{
		check_relative_path(arg, data);
		ret = chdir(arg);
	}
	if (ret != 0)
		return (-1); // TODO error handling with perror
	add_environmentals(data, lastdir);
	return (0);
}
