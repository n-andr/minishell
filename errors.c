/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:55:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/05 16:22:13 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	args_error(void)
{
	ft_putendl_fd("Error. This program does not accept any arguments", STDERR_FILENO);
}

void	malloc_error(void)
{
	ft_putendl_fd("Error. Malloc failed", STDERR_FILENO);
}

void	error_exec(void)
{
	ft_putendl_fd("Error. Process failed", STDERR_FILENO);
}

void	unclosed_quote(void)
{
	ft_putendl_fd("Error. Unclosed quotes", STDERR_FILENO);
	//free stuff if needed
	// return control back to user 
}

void	too_many_args_error(void)
{
	ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
}