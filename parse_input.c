/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:00:10 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/18 16:51:43 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// wee need strings for execve(), so i have desided to go for 2-d array

void	parse_input(char *input, t_minishell *shell)
{
	shell->args = ft_split(input, ' ');
	if (shell->args[0] == NULL) {
		free(input);
		free(shell->args);
	}
}