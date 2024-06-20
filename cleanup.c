/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:40:56 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/20 19:43:07 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_everything(t_data *data)
{
	int	i;

	i = 0;
	while (data->envs[i] != NULL)
	{
		free(data->envs[i]);
		i++;
	}
	free(data->envs);
	free(data->home);
	free(data->pwd);
	free(data->oldpwd);	
}