/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:53:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/21 14:53:16 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 
this function
0. stores the current directory for later
1. checks if the argument is - or nothing (chdir treats '..', '/' 
and '~' automatically, so these are the only two special cases)
2. checks for relative paths
3. checks if the directory change was successful by checking the return value
4. if yes, it updates the environmental values
*/
int	mini_cd(t_data *data)
{
	char 	arg[2] = "-";
	int		ret;
	char	lastdir[MAX_INPUT_SIZE];
	char	newdir[MAX_INPUT_SIZE];

	if (!getcwd(lastdir, sizeof(lastdir)))
		return (-1);
	if (!strcmp(arg, "-"))
		ret = chdir(data->oldpwd);
	else if (!strcmp(arg, ""))
		ret = chdir(data->home);
	else
		ret = chdir(arg);
	if (ret != 0)
		return (-1);
	data->oldpwd = lastdir;
	if (getcwd(newdir, sizeof(newdir)))
		data->pwd = newdir;
	return (0);
}