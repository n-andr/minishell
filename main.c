/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:34:55 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/17 16:03:35 by nandreev         ###   ########.fr       */
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



int	main()
{
	char	user_input[MAX_INPUT_SIZE];
	pid_t	pid;
	int	status;

	while (1)
	{
		write (1, "$ ", 2);
		read_input(user_input);
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
	}
	return (0);
}