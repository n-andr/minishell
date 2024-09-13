/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_redir_commands.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:00:10 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/12 23:26:41 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	starts_with_char(char *str, char c)
{
	if (!str || !str[0])
		return (false);
	if (str[0] == c)
		return (true);
	return (false);
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

char	**add_string_to_array(char **array, char *str)
{
	int		i;
	int		len;
	char	**new_array;

	i = 0;
	len = array_len(array);
	new_array = malloc((len + 2) * sizeof(char *));
	if (!new_array)
		return (NULL);
	while (i < len)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = ft_strdup(str);
	new_array[i + 1] = NULL;
	free_array(array);
	return (new_array);
}
