/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:00:10 by nandreev          #+#    #+#             */
/*   Updated: 2024/08/12 15:15:43 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// wee need strings for execve(), so i have desided to go for 2-d array


static int	preprosess_quotes(char *input, int i, char quote)
{
	while (input[i] != quote && input[i] != '\0')
	{
		if (input[i] == ' ')
			input[i] = '\1'; //change to \1
		i++;
	}
	return(i);
}

// TBD: maybe i need to copy string and free it after instead of changing an initial string
static int	preprosess_string(char *input)
{
	int	i;

	i = 0;
	while(input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = preprosess_quotes(input, i + 1, input[i]);
		if (input[i] == '\0')
		{
			unclosed_quote();
			return (-1);
		}
		i ++;
	}
	return(0);
}

static void	postprosess_array(t_minishell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->args[i] != NULL)
	{
		while (shell->args[i][j] != '\0')
		{
			if (shell->args[i][j] == '\1')
				shell->args[i][j] = ' ';
			j++;
		}
		j = 0;
		i++;
	}
}

int	is_builtin(char *str)
{
	char	*builtins[8];
	int	i;

	if(str == NULL)
		return (0);
	builtins[0] = "cd";
    builtins[1] = "exit";
    builtins[2] = "echo";
    builtins[3] = "pwd";
    builtins[4] = "export";
    builtins[5] = "unset";
    builtins[6] = "env";
    builtins[7] = NULL;
	i = 0;
	while (builtins[i] != NULL)
	{
		if (ft_strcmp(str, builtins[i]) == 0) //not arg 0
			return (1);
		i ++;
	}
	return (0);
}

int 	is_executable(t_minishell *shell, char *str) // not working
{
	char	*tmp;
	char	*newcmd;
	int i;

	if(str == NULL)
		return (0);
	if (access(str, X_OK) == 0)
        return (1);
	else
	{
		i = 0;
		while(shell->paths[i] != NULL)
		{
			tmp = ft_strjoin(shell->paths[i], "/");
			newcmd = ft_strjoin(tmp, str);
			if (access(newcmd, X_OK) == 0)
        		return (1);
			i++;
		}
	}
    return (0);
}

int 	is_path(char *str) //chech for rederections here
{
	if(str == NULL)
		return (0);
	if (ft_strchr(str, '/')) //not arg 0
		return (1);
	else
		return(0);
}

void test_printf(t_minishell *shell) //delete
{
	int	j;
	t_args	*temp;

	j = 0;
	temp = shell->commands;
	while (temp != NULL)
	{
		printf("shell->commands->args:\n");
		while (temp->args[j] != NULL)
		{
			printf("   %s\n", temp->args[j]);
			j++;
		}
		j = 0;
		if (temp->redir == NULL) {
			printf("shell->commands->redir: NULL\n");
		} else {
			printf("shell->commands->redir:\n");
			while (temp->redir[j] != NULL)
			{
				printf("   %s\n", temp->redir[j]);
				j++;
			}
		}
		printf("shell->commands->is_redir: %i\n", temp->is_redir);
		printf("shell->commands->is_pipe: %li\n", temp->is_pipe);
		if (temp->heredoc != NULL) {
			printf("shell->commands->heredoc: %s\n", temp->heredoc);
		} else {
			printf("shell->commands->heredoc: NULL\n");
		}
		printf("shell->commands->next: %p\n", temp->next);
		j = 0;
		temp = temp->next;
	}
}

// if buil-in or executable or path or redirection -> return 1
// error for each command (if two pipes, check two commands -> return 2 errors)
// return: 0 - invalid, 1 - valid
int check_if_cmd_valid(t_minishell *shell)
{
	t_args	*temp;
	int		input_valid;

	input_valid = 1;
	temp = shell->commands;
	while (temp != NULL)
	{
		if (is_builtin(temp->args[0]) 
			|| is_executable(shell, temp->args[0])  
			|| is_path(temp->args[0]))
			temp = temp->next;
		//else if (temp->is_redir == 1)
		else if (temp->is_redir == 1 && temp->args[0] == NULL)
			temp = temp->next;
		else
		{
			printf("%s: command not found\n", temp->args[0]);
			input_valid = 0;
			temp = temp->next;
		}
	}
	return (input_valid);
}

int	parse_input(char *input, t_minishell *shell)
{
	int	i;

	i = preprosess_string(input);
	// what to do with tabs?
	if (i == -1)
	{
		return(-1);
	}
	shell->args = ft_split(input, ' ');
	if (shell->args[0] == NULL) 
	{
		//free(input);
		free(shell->args);
		shell->args = NULL;
	}
	postprosess_array(shell);
	unfold_input(shell);
	organize_struct(shell);
	
	//printing all content of shell->commands
	test_printf(shell); //delete 

	if (check_if_cmd_valid(shell) == 0) // 0 - invalid, 1 - valid
	{
		free_args(shell);
		free_commans(shell);
		return (0);
	}
	else
	{
		//printf("ready to execute\n"); //delete call executer here or retern to main
		free_args(shell);
		return (1);
	}
	return (0);
}
