/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:39:23 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/17 17:58:37 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_envs(char **env)
{
	t_data	data;
	int		i;

	data.envs = (char**)malloc(sizeof(char**)); // fix malloc with right size
	if (!data.envs)
		return (NULL);
	i = 0;
	while(env[i] != NULL)
	{
		data.envs[i] = ft_strdup(env[i]);
		// add function to free array if malloc does't work
		i++;
	}
}