/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:39:23 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/18 12:35:02 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// When the program starts running, this function copies the environmental 
// values into a struct
void	init_environmentals(char **env)
{
	t_data	data;
	int		i;

	i = 0;
	while (env[i])
		i++;
	data.envs = (char **)malloc(sizeof(char *) * (i + 1));
	if (!data.envs)
		malloc_error();
	i = 0;
	while (env[i] != NULL)
	{
		data.envs[i] = ft_strdup(env[i]);
		if (!data.envs[i])
		{
			while (i > 0)
				free(data.envs[i - 1]);
			free(data.envs);
			malloc_error();
		}
		i++;
	}
}
