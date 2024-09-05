/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:55:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/05 13:35:35 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	args_error(void)
{
	write(STDERR_FILENO, "Error. This program does not accept any arguments\n", 51);
}

void	malloc_error(void)
{
	write(STDERR_FILENO, "Error. Malloc failed\n", 22);
}

void	error_exec(void)
{
	write(STDERR_FILENO, "Error. Process failed\n", 23);
}

void	unclosed_quote(void)
{
	write(STDERR_FILENO, "Error. Unclosed quotes\n", 24);
	//free stuff if needed
	// return control back to user 
}

void	too_many_args_error(void)
{
	write(STDERR_FILENO, "cd: too many arguments\n", 24);
}