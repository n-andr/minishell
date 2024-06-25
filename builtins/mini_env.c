/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:07:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/25 12:33:12 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	mini_env(t_data *data)
{
	int i;

	i = 0;
	while (data->envs[i] != NULL)
	{
		printf("%s\n", data->envs[i]);
		i++;
	}
	return (0);
}
