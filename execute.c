/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:23:44 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/10 13:55:20 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd(t_minishell *shell, t_args *command)
{	
	char	*cmd;
	char	*tmp;
	char	*newcmd;
	
	check_redirections(command);
	cmd = ft_strdup(command->args[0]);
	if(!access(cmd, F_OK))
		execve(cmd, command->args, shell->envs);
	else
	{
		int i;

		i = 0;
		while(shell->paths[i] != NULL)
		{
			tmp = ft_strjoin(shell->paths[i], "/");
			newcmd = ft_strjoin(tmp, cmd);
			if(!access(newcmd, F_OK))
				execve(newcmd, shell->commands->args, shell->envs);
			i++;
		}
	}
	perror("Could not execve");
	return (0);
}

static int	scanifbuiltin(t_args *cmd, t_minishell *shell)
{
	if(!ft_strcmp("pwd", cmd->args[0]))
		return (mini_pwd(shell), 1);
	else if(!ft_strcmp("cd", cmd->args[0]))
		return (mini_cd(shell), 1);
	else if(!ft_strcmp("env", cmd->args[0]))
		return (mini_env(shell), 1);
	else if(!ft_strcmp("unset", cmd->args[0]))
		return (mini_unset(shell, "MAIL="), 1); // to be corrected
//	else if(!ft_strcmp("echo", shell->args[0]))
//		return (mini_echo(data), 1);
	else
		return (0);
}

int testing_init(t_minishell *shell)
{
	// now implemented commands as an array but should actually be a linked list
	// args and redir are arrays
	
	shell->commands = malloc(2 * sizeof(t_args));
	if (!shell->commands)
		return (0);
	shell->commands[0].args = (char **)malloc((4 * sizeof(char*)));
	if (!shell->commands[0].args)
		return (0);
	shell->commands[0].args[0] = "grep"; // "/usr/bin/cat";
	shell->commands[0].args[1] = "some";
	shell->commands[0].args[2] = "testpoem.txt";
	shell->commands[0].args[3] = NULL;
	shell->commands[0].is_pipe = 0;

	/* shell->commands[1].args = (char **)malloc((3 * sizeof(char*)));
	if (!shell->commands[1].args)
		return (0);
	shell->commands[1].args[0] = "rev";
	shell->commands[1].args[1] = NULL;
	shell->commands[1].args[2] = NULL;
	shell->commands[1].is_pipe = 0; */
	
	shell->commands[0].redir = (char **)malloc(1 * sizeof(char *));
	if (!shell->commands[0].redir)
		return (0);
	shell->commands[0].redir[0] = NULL;
	shell->commands[1].redir = (char **)malloc(1 * sizeof(char *));
	if (!shell->commands[1].redir)
		return (0);
	shell->commands[1].redir[0] = NULL;
	/* shell->commands->redir[0] = ">>";
	shell->commands->redir[1] = "test.txt";
	shell->commands->redir[2] = ">";
	shell->commands->redir[3] = "test2.txt";
	shell->commands->redir[4] = NULL;
	shell->commands->redir = (char **)malloc((3) * sizeof(char *));
	shell->commands->redir[0] = "<<";
	shell->commands->redir[1] = "EOF"; */	
	
	return (1);
}

int single_cmd(t_minishell *shell, t_args *cmd)
{
	pid_t	pid;
	int		status;
	
	if (scanifbuiltin(cmd, shell))
	// 	return (1);
	handle_heredoc(shell); // check where this should go
	pid = fork();
	if (pid < 0)
	{
		error_exec();
		return (0);
	}
	if (pid == 0)
		handle_cmd(shell, cmd);
	else
		waitpid(pid, &status, 0);
	return (1);
}

int	execute(t_minishell *shell)
{
	int	i;
	
	if (!testing_init(shell)) // to be deleted
		return (0);
	// if (shell->commands[0].args[0] == NULL || shell->commands[0].args[0][0] == '\0')
	//	return (0);
	i = 0;
	if (shell->commands[0].is_pipe == 0)
	{
		single_cmd(shell, &shell->commands[0]);
		return (1);
	}
	// while (shell->commands[i].args != NULL) // implemented it as an array now
	// {
		// if (shell->commands[i].is_pipe == 0)
		// 	single_cmd(shell, &shell->commands[i]);
		// handle_heredoc(shell);
	else
	{
		ft_pipe(shell, &shell->commands[0]);
	}		
		// i++;
	// }
	return (1);
}