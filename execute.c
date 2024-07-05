/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:23:44 by lde-taey          #+#    #+#             */
/*   Updated: 2024/07/05 16:05:00 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd(t_minishell *shell)
{	
	char	*cmd;
	char	*tmp;
	char	*newcmd;
	
	check_redirections(shell);
	cmd = ft_strdup(shell->commands->args[0]);
	if(!access(cmd, F_OK))
		execve(cmd, shell->commands->args, shell->envs);
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
			free (newcmd);
			i++;
		}
	}
	perror("Could not execve");
	return (0);
}

static int	scanifbuiltin(char *str, t_minishell *shell)
{
	if(!ft_strcmp("pwd", str))
		return (mini_pwd(shell), 1);
	else if(!ft_strcmp("cd", str))
		return (mini_cd(shell), 1);
	else if(!ft_strcmp("env", str))
		return (mini_env(shell), 1);
	else if(!ft_strcmp("unset", str))
		return (mini_unset(shell, "MAIL="), 1);
//	else if(!ft_strcmp("echo", str))
//		return (mini_echo(data), 1);
	else
		return (0);
}

int	execute(char *str, t_minishell *shell) // change according to way args are parsed into structs
{
	pid_t	pid;
	int		status;
	
	shell->commands = malloc(sizeof(t_args));
	if (!shell->commands)
		return (0);
	shell->commands->args = (char **)malloc((3 * sizeof(char*)));
	if (!shell->commands->args)
		return (0);
	shell->commands->args[0] = "cat"; // "/usr/bin/cat";
	shell->commands->args[1] = "errors.c";
	shell->commands->args[2] = NULL;
	shell->commands->redir = (char **)malloc(1 * sizeof(char *));
	if (!shell->commands->redir)
		return (0);
	shell->commands->redir[0] = NULL;

	// check if arguments are empty
	// call expander (?)
	if (scanifbuiltin(str, shell))
		return (1);
	handle_heredoc(shell);
	pid = fork();
	if (pid < 0)
	{
		error_exec();
		return (0);
	}
	if (pid == 0)
		handle_cmd(shell);
	else
		waitpid(pid, &status, 0);
	return (1);
}