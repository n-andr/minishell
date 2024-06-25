/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:20:49 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/25 14:12:07 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	equalsign(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '=')
			return (i + 1);
	}
	return (-1);
}

void	delete_var(char **envs, char *str)
{
	int	i;
	int j;
	int pos_eq;

	i = 0;
	j = 0;
	pos_eq = equalsign(str);
	while(envs[i] != NULL)
	{
		if (!ft_strncmp(envs[i], str, ft_strlen(str + 1))) // TODO check if this works
		{
			j = 0;
			while(envs[i][j] != '\0')
			{
				ft_bzero(envs[i][j] + pos_eq, (ft_strlen(envs[i]) - pos_eq - 1));
				j++;
			}
		}
		i++;
	}
}

int	check_if_valid(char *str)
{
	int	i;

	i = 0;
	if(str[0] == '\0' || !str)
		return (0);
	if (equalsign(str) < 0)
		return (0);
	while(str[i])
	{
		if (str[i] == '/') // ? what to do here?
			return (0);
		i++;
	}
	return (1);
}

int	mini_unset(t_data *data, char *str)
{
	if (!check_if_valid(str))
		return (0);
	delete_var(data->envs, str); // what about malloc?
	return (1);
}