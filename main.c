/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:34:55 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/17 16:24:07 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	read_input(char *input)
{
	int	i;

	if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
	{
		write(2, "Error reading input\n", 20);
		_exit(1);
	}

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\n')
		{
			input[i] = '\0';
			break ;
		}
		i++;
	}
	//printf("%s", input);
}

void	print_message(void)
{
	write(1, "command not supported yet\n", 26);
}



int	main(int argc, char **argv)
{
	char	user_input[MAX_INPUT_SIZE];
	pid_t	pid;
	int	status;

	// 1. handle arguments
	if (argc != 1 || argv[1])
		return (error_message()); // TODO
	//	1a. store environment variables from the parent process in a struct
	//	1b. add data about current directory and other states to struct
	
	// Read-Eval-Print Loop
	while (1)
	{
		//	2. display prompt message
		write (1, "$ ", 2);
		//	3. listen for input with a getline function
		read_input(user_input);
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
			print_message();
		else
		{
			waitpid(pid, &status, 0);
		}
		//	8. free memory

	}
	return (0);
}