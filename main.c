/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:34:55 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/21 16:06:01 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(char *input)
{
	int	i;

	// TODO replace fgets with other function
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

int	main(int argc, char **argv, char **envp)
{
	// char	user_input[MAX_INPUT_SIZE];
	t_data	data;

	// 1. handle arguments
	if (argc != 1 || argv[1])
		return (args_error(), -1);
	//	1a. store environment variables from the parent process in a struct
	init_environmentals(envp, &data);
	//	1b. add data about current directory and other states to struct
	
	// Read-Eval-Print Loop
	/* while (1)
	{
		//	2. display prompt message
		// write (1, "$ ", 2);
		//	3. listen for input with a getline function
		// read_input(user_input);
		// 4. build lexer that scans input and puts everything in an array
		// 5. parse array and put everything into an execution tree
		// 6. expand (add information about environment to execution tree)
		// 7. execute the commands with a fork
		// execute("pwd", &data);
		//	8. free memory
	} */
	execute("cd", &data);
	// execute("cd", &data);
	free_everything(&data);
	return (0);
}