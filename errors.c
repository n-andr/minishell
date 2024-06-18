/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:55:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/06/18 16:00:21 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO write to STDERR instead of STDOUT 
void	args_error(void)
{
	printf("Error. This program does not accept any arguments\n");
	exit(-1);
}

void	malloc_error(void)
{
	printf("Error. Malloc failed\n");
	exit(-1);
}

void	error_exec(void)
{
	printf("Error. Process failed\n");
	exit(-1);
}