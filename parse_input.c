/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:00:10 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/13 02:19:45 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	preprosess_quotes(char *input, int i, char quote)
{
	while (input[i] != quote && input[i] != '\0')
	{
		if (input[i] == ' ')
			input[i] = '\1';
		i++;
	}
	return (i);
}

static char	*insert_spaces(char *input, int i, int len)
{
	char	*new_input;
	int		j;
	int		k;

	j = 0;
	k = 0;
	new_input = malloc((ft_strlen(input) + 3) * sizeof(char));
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

// static int	insert_spaces(char **input, int char_position, int len)
// {
// 	char	*new_input;
// 	int		j;
// 	int		k;

// 	j = 0;
// 	k = 0;
// 	new_input = malloc((ft_strlen(*input) + 3) * sizeof(char)); // 3 = for 2 spaces and \0
// 	if (!new_input)
// 		return (-1);
// 	while ((*input)[j] != '\0')
// 	{
// 		if (j == char_position)
// 		{
// 			new_input[k++] = ' ';
// 			while ((len--) > 0)
// 				new_input[k++] = (*input)[j++];
// 			new_input[k++] = ' ';
// 		}
// 		else
// 			new_input[k++] = (*input)[j++];
// 	}
// 	new_input[k] = '\0';
// 	free(*input);
// 	*input = new_input;
// 	return (char_position + len + 1);
// }



// static int preprosess_pipe_redir(char **input, int i, int j)
// {
// 	if ((*input)[i] == '|')
// 	{
// 		j = i + 1;
// 		while ((*input)[j] == ' ')
// 			j++;
// 		if ((*input)[i + 1] == '|' || (*input)[j] == '|' 
// 			|| (*input)[i + 1] == '\0' || (*input)[j] == '\0')
// 			return (pipe_error());
// 		else
// 		{
// 			return (insert_spaces(input, i, 1));
// 		}
// 	}
// 	else if ((*input)[i] == '<' || (*input)[i] == '>')
// 	{
// 		if ((*input)[i + 1] == (*input)[i])
// 		{
// 			return (insert_spaces(input, i, 2));
// 		}
// 		else
// 		{
// 			return (insert_spaces(input, i, 1));
// 		}
// 	}
// 	return (i);
// }

// TBD: maybe i need to copy string and free it after instead of changing an initial string
// to do: pipe and redir check here !!!
// replace tabs with spaces

// static int	preprosess_string(char **input)
// {
// 	int	i;

// 	i = 0;
// 	while((*input)[i] != '\0')
// 	{
// 		if ((*input)[i] == '\'' || (*input)[i] == '\"')
// 			i = preprosess_quotes((*input), i + 1, (*input)[i]);
// 		if ((*input)[i] == '\0')
// 		{
// 			unclosed_quote();
// 			return (-1);
// 		}
// 		if ((*input)[i] == '|' || (*input)[i] == '<' || (*input)[i] == '>')
// 		{
// 			i = preprosess_pipe_redir(input, i, i);
// 			if (i == -1)
// 				return (-1);
// 		}
// 		if((*input)[i] == 9)
// 			(*input)[i] = ' ';
// 		i ++;
// 	}
// 	return(0);
// }

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
	organize_struct(shell);
	free_args(shell);
	shell->args = NULL;
	return (1);
}
