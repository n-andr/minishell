/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:39:23 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/20 19:55:50 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_pwd(t_data *data)
{
	int	i;

	i = 0;
	while(data->envs[i] != NULL)
	{
		if (!ft_strncmp(data->envs[i], "PWD=", 4))
		{
			data->pwd = ft_strdup(data->envs[i] + 4);
			if (!data->pwd)
				malloc_error (); // extra cleanup?
			// printf("%s\n", data->pwd);

		}
		else if (!ft_strncmp(data->envs[i], "OLDPWD=", 7))
		{
			data->oldpwd = ft_strdup(data->envs[i] + 7);
			if (!data->oldpwd)
				malloc_error ();
			// printf("%s\n", data->oldpwd);

		}
		else if (!ft_strncmp(data->envs[i], "HOME=", 5))
		{
			data->home = ft_strdup(data->envs[i] + 5);
			if (!data->home)
				malloc_error ();
			// printf("%s\n", data->home);
		}
		i++;
	}
}

// When the program starts running, this function copies the environmental 
// values into a struct
void	init_environmentals(char **env, t_data *data)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	data->envs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data->envs)
		malloc_error();
	i = 0;
	while (env[i] != NULL)
	{
		data->envs[i] = ft_strdup(env[i]);
		if (!data->envs[i])
		{
			while (i > 0)
				free(data->envs[i - 1]);
			free(data->envs);
			malloc_error();
		}
		// printf("%s\n", data->envs[i]);
		i++;
	}
	data->envs[i] = NULL;
	store_pwd(data);
}
