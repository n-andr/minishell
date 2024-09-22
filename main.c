/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:34:55 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/22 21:22:39 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	g_sigint_received;

void	initiate_null(t_minishell *shell)
{
	shell->args = NULL;
	shell->envs = NULL;
	shell->pwd = NULL;
	shell->oldpwd = NULL;
	shell->paths = NULL;
	shell->home = NULL;
	shell->commands = NULL;
	shell->exit_code = 0;
	g_sigint_received = 0;
}

int	main(int argc, char **argv, char **envp)
{
	char		*user_input;
	t_minishell	shell;

	signal_config_input();
	initiate_null(&shell);
	if (argc != 1 || argv[1])
		return (args_error(), -1);
	init_environmentals(envp, &shell);
	while (1)
	{
		user_input = readline("minishell$ ");
		if (user_input == NULL)
		{
			write (STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (user_input != NULL && ft_strlen(user_input) > 0)
		{
			add_history(user_input);
			if (parse_input(user_input, &shell) == 1)
				execute(&shell);
		}
	}
	free_everything(&shell);
	return (0);
}
