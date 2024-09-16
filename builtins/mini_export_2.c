/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini-export2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:51:26 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/16 23:47:42 by nandreev         ###   ########.fr       */
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
