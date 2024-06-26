/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:34:55 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/26 17:17:11 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*user_input;
	pid_t	pid;
	t_minishell	shell;
	int	status;
	shell.args = NULL;
	
	// 1. handle arguments
	if (argc != 1 || argv[1])
		return (args_error(), -1);
	//	1a. store environment variables from the parent process in a struct
	init_environmentals(envp, &shell);
	//	1b. add data about current directory and other states to struct
	
	// Read-Eval-Print Loop
	while (1)
	{
		//	2. display prompt message
		//	3. listen for input with a getline function
		user_input = readline("minishell$ ");
		if (user_input == NULL)
			break;
		if (ft_strlen(user_input) > 0) // ignore empty input
			add_history(user_input);
		parse_input(user_input, &shell);
		// 4. build lexer that scans input and puts everything in an array
		// 5. parse array and put everything into an execution tree
		// 6. expand (add information about environment to execution tree)
		// 7. execute the commands with a fork
		pid = fork();
		
		if (pid < 0) // error
		{
			write(2, "Fork failed\n", 12);
			exit(1);
		}
		if (pid == 0) //call child process
			execute(&shell);
		else
		{
			waitpid(pid, &status, 0);
		}
		//	8. free memory
	}
	// execute("unset", &shell);
	free_everything(&shell);
	return (0);
}