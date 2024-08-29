/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:55:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/08/29 15:06:13 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO write to STDERR instead of STDOUT 
void	args_error(void)
{
	printf("Error. This program does not accept any arguments\n");
	// exit(-1);
}

void	malloc_error(void)
{
	printf("Error. Malloc failed\n");
	// exit(-1);
}

void	error_exec(void)
{
	printf("Error. Process failed\n");
	// exit(-1);
}

void	unclosed_quote(void)
{
	printf("Error. Unclosed quotes\n");
	//free stuff if needed
	// return control back to user 
}

void	too_many_args_error(void)
{
	write(STDERR_FILENO, "cd: too many arguments\n", 24);
}