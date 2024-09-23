/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 14:46:29 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/23 12:08:37 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	signal_config_child(void)
// {
// 	struct sigaction	signal_act;

// 	signal_act.sa_handler = SIG_IGN;
// 	// sigemptyset(&signal_act.sa_mask);
// 	// signal_act.sa_flags = 0;
// 	sigaction(SIGINT, &signal_act, NULL);
// 	signal_act.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &signal_act, NULL);
// }

void	signal_config_execute(void)
{
	struct sigaction	signal_act;

	signal_act.sa_handler = sigint_handler_exec;
	sigemptyset(&signal_act.sa_mask);
	signal_act.sa_flags = 0;
	sigaction(SIGINT, &signal_act, NULL);
	signal_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signal_act, NULL);
}

void	signal_config_input(void)
{
	struct sigaction	signal_act;

	signal_act.sa_handler = sigint_handler_input;
	sigemptyset(&signal_act.sa_mask);
	signal_act.sa_flags = 0;
	sigaction(SIGINT, &signal_act, NULL);
	signal_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signal_act, NULL);
}

void	signal_config_heredoc(void)
{
	struct sigaction	signal_act;

	signal_act.sa_handler = sigint_handler_heredoc;
	sigemptyset(&signal_act.sa_mask);
	signal_act.sa_flags = 0;
	sigaction(SIGINT, &signal_act, NULL);
	signal_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signal_act, NULL);
}
