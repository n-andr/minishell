/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:51:26 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/28 02:23:29 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*preprocess_var(char *arg)
{
	char	*new_var;
	int		total_len;

	total_len = ft_strlen(arg);
	new_var = NULL;
	new_var = malloc(sizeof(char) * (total_len + 1));
	if (!new_var)
		return (NULL);
	ft_strlcpy(new_var, arg, total_len + 1);
	return (new_var);
}

int	add_var(char *arg, int name_len, t_minishell *shell)
{
	char	*new_var;

	new_var = preprocess_var(arg);
	if (var_exists(arg, name_len, new_var, shell) == 1)
	{
		return (0);
	}
	else
	{
		shell->envs = realloc_env_array(shell->envs, new_var);
	}
	return (0);
}

char	**copy_array(char **new_array, char **old_array)
{
	int	i;

	i = 0;
	while (old_array[i] != NULL)
		i++;
	new_array = malloc(sizeof(char *) * (i + 1));
	if (!new_array)
		return (NULL);
	i = 0;
	while (old_array[i] != NULL)
	{
		new_array[i] = ft_strdup(old_array[i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}

char	**sort_alphabetically(char **envs)
{
	int		i;
	int		j;
	char	*temp;
	char	**export;

	i = 0;
	j = 0;
	export = NULL;
	export = copy_array(export, envs);
	while (export[i] != NULL)
	{
		j = i + 1;
		while (export[j] != NULL)
		{
			if (ft_strcmp(export[i], export[j]) > 0)
			{
				temp = export[i];
				export[i] = export[j];
				export[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (export);
}
