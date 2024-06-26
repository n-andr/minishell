/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:09:29 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/26 12:33:42 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_input(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	mini_exit(t_data *data, char *str)
{
	// check if input is valid for exit command
	if (check_input(str))
		return (-1);
	// free everything
	// determine exit code and exit
	return (0);
}