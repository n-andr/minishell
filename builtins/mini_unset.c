/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 12:20:49 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/26 12:14:36 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	where_is_equalsign(char *str)
{
	int i;

	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (-1);
}

void	delete_var(char **envs, char *str)
{
	int	i;
	int pos_eq;

	i = 0;
	pos_eq = where_is_equalsign(str);
	while(envs[i] != NULL)
	{
		if (!ft_strncmp(envs[i], str, ft_strlen(str)))
			ft_bzero(envs[i] + pos_eq, (ft_strlen(envs[i]) - pos_eq + 1));
		i++;
	}
}

int	check_if_valid(char *str)
{
	int	i;

	i = 0;
	if(str[0] == '\0' || !str)
		return (0);
	if (where_is_equalsign(str) < 0) // TODO check with bash: is equal sign
	// needed in input
		return (0);
	while(str[i] != '\0')
	{
		if (str[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

int	mini_unset(t_data *data, char *str)
{
	if (!check_if_valid(str))
		return (1);
	delete_var(data->envs, str);
	// mini_env(data); // test
	return (0);
}