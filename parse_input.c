/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:00:10 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/11 13:20:35 by nandreev         ###   ########.fr       */
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

static char *insert_spaces(char *input, int i, int len)
{
	char	*new_input;
	int		j;
	int		k;

	j = 0;
	k = 0;
	new_input = malloc((ft_strlen(input) + 3) * sizeof(char)); // 3 = for 2 spaces and \0
	if (!new_input)
		return (NULL);
	while (input[j] != '\0')
	{
		if (j == i)
		{
			new_input[k] = ' ';
			k++;
			while (len > 0)
			{
				new_input[k] = input[j];
				j++;
				k++;
				len--;
			}
			new_input[k] = ' ';
			k++;
		}
		else
		{
			new_input[k] = input[j];
			j++;
			k++;
		}
	}
	new_input[k] = '\0';
	free(input);
	return (new_input);
}

static int preprosess_pipe_redir(char **input, int i)
{
	if ((*input)[i] == '|')
	{
		if ((*input)[i + 1] == '|')
		{
			write(2, "minishell: syntax error near '|'\n", 33);
			return (-1);
		}
		else
		{
			//pipe
			(*input) = insert_spaces((*input), i, 1);
			i += 2;
		}
	}
	else if ((*input)[i] == '<')
	{
		if ((*input)[i + 1] == '<')
		{
			//redir << 
			(*input) = insert_spaces((*input), i, 2);
			i += 3;
		}
		else
		{
			// redir <
			(*input) = insert_spaces((*input), i, 1);
			i += 2;
		}
		
	}
	else if ((*input)[i] == '>')
	{
		if ((*input)[i + 1] == '>')
		{
			//redir >> 
			(*input) = insert_spaces((*input), i, 2);
			i += 3;
		}
		else
		{
			// redir >
			(*input) = insert_spaces((*input), i, 1);
			i += 2;
		}
	}
	return (i);
}

// TBD: maybe i need to copy string and free it after instead of changing an initial string
// to do: pipe and redir check here !!!
// replace tabs with spaces

static int	preprosess_string(char **input)
{
	int	i;

	i = 0;
	while((*input)[i] != '\0')
	{
		if ((*input)[i] == '\'' || (*input)[i] == '\"')
			i = preprosess_quotes((*input), i + 1, (*input)[i]);
		if ((*input)[i] == '\0')
		{
			unclosed_quote();
			
			return (-1);
		}
		if ((*input)[i] == '|' || (*input)[i] == '<' || (*input)[i] == '>')
		{
			i = preprosess_pipe_redir(input, i);
			if (i == -1)
				return (-1);
		}
		if((*input)[i] == 9)
			(*input)[i] = ' ';
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



void test_printf(t_minishell *shell) //delete
{
	int	j;
	t_args	*temp;

	j = 0;
	temp = shell->commands;
	while (temp != NULL)
	{
		if (temp->args == NULL) {
			printf("shell->commands->args: NULL\n");
		} else {
			printf("shell->commands->args:\n");
			while (temp->args[j] != NULL)
			{
				printf("   %s\n", temp->args[j]);
				j++;
			}
			j = 0;
		}
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
		printf("shell->commands->previous: %p\n", temp->previous);
		printf("shell->commands->next: %p\n\n", temp->next);
		j = 0;
		temp = temp->next;
	}
}

void test_printf_command(t_args	*temp) //delete
{
	int	j;
	j = 0;
	if (temp == NULL)
	{
		printf("shell->commands: NULL\n");
	}


	if (temp->args == NULL) {
		printf("shell->commands->args: NULL\n");
	} else {
		printf("shell->commands->args:\n");
		while (temp->args[j] != NULL)
		{
			printf("   %s\n", temp->args[j]);
			j++;
		}
		j = 0;
	}
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
	printf("shell->commands->previous: %p\n", temp->previous);
	printf("shell->commands->next: %p\n\n", temp->next);
	j = 0;
	
}

// if buil-in or executable or path or redirection -> return 1
// error for each command (if two pipes, check two commands -> return 2 errors)
// return: 0 - invalid, 1 - valid



int	parse_input(char *input, t_minishell *shell)
{
	int	i;
	char	*temp;

	temp = malloc(ft_strlen(input) + 1);
	if (!temp)
		return (-1);
	ft_strlcpy(temp, input, ft_strlen(input) + 1);
	free(input);
	i = preprosess_string(&temp);
	if (i == -1)
	{
		free(temp);
		shell->exit_code = 2; //to be checked
		return(-1);
	}
	// // printing input string after preprosessing
	// printf("temp: %s\n", temp); //delete 
	
	shell->args = ft_split(temp, ' ');
	free(temp);
	if (shell->args[0] == NULL) 
	{
		free(shell->args);
		shell->args = NULL;
		shell->exit_code = 0;
		return (0); //nothing to do
	}
	postprosess_array(shell);
	// unfold_input(shell);
	// shell->exit_code = 0; // must be after unfold
	organize_struct(shell);

	//test_printf(shell); //delete 
	
	//unfold_struct(shell);
	//shell->exit_code = 0; // moved inside check_cmd_valid must be after unfold
	
	//printing all content of shell->commands
	// printf("\n\nafter unfolding: \n");
	// test_printf(shell); //delete 

	free_args(shell);

	// if (check_if_cmd_valid(shell) == 0) // 0 - invalid, 1 - valid
	// {
	// 	free_commands(shell);
	// 	shell->exit_code = 127; // bash exit code
	// 	return (0); 
	// }
	// else
	// {
	// 	//printf("ready to execute\n"); //delete
	// 	return (1);
	// }
	return (1);
}
