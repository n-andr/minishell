/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:46:29 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/11 12:26:43 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_signals(void)
{
	signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_config(void)
{
	struct sigaction	signal_act;
	
	signal_act.sa_handler = sigint_handler;
	sigemptyset(&signal_act.sa_mask);
	signal_act.sa_flags = 0;
	sigaction(SIGINT, &signal_act, NULL);
	signal_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signal_act, NULL);
}
