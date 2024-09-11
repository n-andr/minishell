/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:55:11 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/11 16:02:56 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	args_error(void)
{
	ft_putstr_fd("Error. ", STDERR_FILENO);
	ft_putstr_fd("This program does not accept any arguments\n", STDERR_FILENO);
}

void	malloc_error(t_minishell *shell)
{
	ft_putendl_fd("Error. Malloc failed", STDERR_FILENO);
	free_everything(shell);
	exit(EXIT_FAILURE);
}

void	error_exec(void)
{
	ft_putendl_fd("Error. Process failed", STDERR_FILENO);
}

void	unclosed_quote(void)
{
	ft_putendl_fd("Error. Unclosed quotes", STDERR_FILENO);
	// free stuff if needed
	// return control back to user 
}

void	too_many_args_error(void)
{
	ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
}
