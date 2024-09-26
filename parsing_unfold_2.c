/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unfold_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:51:12 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/26 14:41:46 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *var_name, t_minishell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (shell->envs[i] != NULL)
	{
		if (ft_strncmp(shell->envs[i], var_name, len) == 0
			&& (shell->envs[i][len] == '=' || shell->envs[i][len] == '\0'))
			return (ft_strdup(shell->envs[i] + len + 1));
		i++;
	}
	return (NULL);
}

char	*getvar(char *str, int *i, t_minishell *shell, char *unfold)
{
	char	*temp;
	char	*var_expanded;

	var_expanded = expand_variable(str, i, shell);
	temp = ft_strjoin(unfold, var_expanded);
	unfold = free_and_assign(unfold, temp, var_expanded);
	return (unfold);
}

// get the substring from the start to the current position,
// then get the variable expanded value and add it to the substring

char	*expand_variable(char *str, int *i, t_minishell *shell)
{
	char	*var_name;
	char	*var_value;
	int		start;
	int		len;

	start = (*i) + 1;
	if (is_valid_name(str[*i + 1], i) == false)
		return (ft_strdup("$"));
	(*i)++;
	if (str[*i] == '?')
		return (get_exit_code(shell, i));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	len = *i - start;
	var_name = ft_substr(str, start, len);
	if (!var_name)
		return (NULL);
	var_value = get_env_value(var_name, shell);
	free(var_name);
	if (var_value)
		return (var_value);
	else
		return (ft_strdup(""));
}

char	*unfold_double(char *str, int *i, t_minishell *shell)
{
	int		start;
	char	*unfolded;
	char	*temp;
	char	*substing;

	unfolded = ft_strdup("");
	start = ++(*i);
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			substing = ft_substr(str, start, *i - start);
			temp = ft_strjoin(unfolded, substing);
			unfolded = free_and_assign(unfolded, temp, substing);
			unfolded = getvar(str, i, shell, unfolded);
			start = *i;
		}
		else
			(*i)++;
	}
	substing = ft_substr(str, start, *i - start);
	temp = ft_strjoin(unfolded, substing);
	unfolded = free_and_assign(unfolded, temp, substing);
	(*i)++;
	return (unfolded);
}
