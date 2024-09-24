/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:54:38 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/24 15:50:30 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	terminal_setup(struct termios orig_termios)
// {
// 	struct termios	raw;

// 	// tcgetattr(STDIN_FILENO, &orig_termios);
// 	raw = orig_termios;
// 	raw.c_lflag &= ~(ICANON); // | ECHO);
// 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); // check if I have to do sth with fds in case of a pipe
// }

// void	terminal_reset(struct termios orig_termios)
// {
// 	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
// }

// int	custom_read(void)
// {
// 	char c;

// 	if(read(STDIN_FILENO, &c, 1) == 1)
// 		return (c);
// 	return EOF;	
// }

void	setupfork(t_minishell *shell, t_args *cmd)
{
	pid_t	pid;
	int		status;
	char	buffer[MAX_INPUT_SIZE];
	ssize_t	bytes_read;

	status = 0;
	signal_config_children();
	// terminal_setup(shell->orig_termios); // do this in pipe as well?
	pid = fork();
	if (pid < 0)
	{
		error_exec();
		return ;
	}
	if (pid == 0)
		handle_cmd(shell, cmd); // maybe add terminal_reset here
	// terminal_setup(shell->orig_termios);
	while (isatty(STDIN_FILENO)) // && (waitpid(pid, &status, 0) == 0))
	{
		while(waitpid(pid, &status, 0) == 0)
		{
			// user_input = readline("");
			// if (user_input == NULL)
			// {
			// 	write (STDOUT_FILENO, "exit\n", 5);
			// 	kill(pid, SIGTERM);
			// 	waitpid(pid, &status, 0);
			// 	// cleanup?
			// 	exit(0);
			// }
			bytes_read = read(STDIN_FILENO, buffer, MAX_INPUT_SIZE);
			if (bytes_read == 0) // it never gets here
			{
				ft_putendl_fd("exit", STDOUT_FILENO);
				kill(pid, SIGTERM);
				waitpid(pid, &status, 0);
				exit(0);
			}
			ft_putstr_fd(buffer, STDOUT_FILENO);
		}
		if (waitpid(pid, &status, 0) != 0)
		 	break;
	}
		// 	
		// }
		// if (waitpid(pid, &status, 0) != 0)
		// 	break;
		//	ft_putchar_fd('\n', STDOUT_FILENO);
	// }
	// while ((c = custom_read()) != EOF) 
	// {
	// 	if (c == 4) // ASCII code for Ctrl+D
	// 	{ 
	// 		kill(pid, SIGTERM);
	// 		break;
    //     }
	// 	else if (c != 28) // ASCII code for Ctrl+
	// 	{
	// 		write(STDOUT_FILENO, &c, 1); // this should actually write to the struct?
	// 		if (c != '\n') 
	// 		{
	// 			write(STDOUT_FILENO, &c, 1);
	// 		}
	// 	}
    // }
	// if (buffer[0] == 4)
	// {
	// 	ft_putendl_fd("exit", STDERR_FILENO); // stdout?
 	// 	exit(0);
	// }
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		shell->exit_code = WEXITSTATUS(status);
	else
		shell->exit_code = EXIT_FAILURE;
	// terminal_reset(shell->orig_termios);
}

void	single_cmd(t_minishell *shell, t_args *cmd)
{
	expand_command(shell, cmd);
	if (cmd->cmd_valid == false)
		return ;
	if (handle_heredoc(cmd) == 1)
	{
		shell->exit_code = 2;
		return ;
	}
	if (cmd->args == NULL || cmd->args[0] == NULL)
		return ;
	if (scanifbuiltin(cmd) == 1)
	{
		save_fds(shell);
		if (check_redirections(cmd) == 1)
		{
			shell->exit_code = EXIT_FAILURE;
			return ;
		}
		shell->exit_code = execbuiltin(shell, cmd);
		reset_fds(shell);
		return ;
	}
	setupfork(shell, cmd);
}
