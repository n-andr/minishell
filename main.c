/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:34:55 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/25 21:27:09 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_message(t_minishell *shell)
{
	int i = 0;
	// while (shell->args[i]) // testing if everything is parsed correctly
	// {
	// 	printf("args: %s\n", shell->args[i]);
	// 	i ++;
	// }
	
	write(1, "command not supported yet\n", 26);
	i = 0;
	while (shell->args[i]) // free args
	{
		free (shell->args[i]);
		i ++;
	}
	shell->args = NULL;
}

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
	init_environmentals(envp);
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
			print_message(&shell);
		else
		{
			waitpid(pid, &status, 0);
		}
		//	8. free memory

	}
	return (0);
}