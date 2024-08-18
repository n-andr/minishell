/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_input_in_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:05:17 by nandreev          #+#    #+#             */
/*   Updated: 2024/08/17 02:40:22 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//WIP add to makefile when ready



t_args	*init_new_command(void)
{
	t_args	*new_command;

	new_command = malloc(sizeof(t_args));
	if (!new_command)
		return NULL;
	new_command->args = NULL;
	new_command->redir = NULL;
	new_command->is_redir = false;
	new_command->is_pipe = 0;
	new_command->heredoc = NULL;
	new_command->next = NULL;
	return (new_command);
}

void add_command(t_minishell *shell, t_args *new_command) 
{
	t_args	*current;

	if (!shell->commands) 
	{
		shell->commands = new_command;
	} 
	else 
	{
		current = shell->commands;
		while (current->next) 
		{
			current = current->next;
		}
		current->next = new_command;
	}
}

char **realloc_array(char **array, size_t new_size)
{
	char	**new_array;
	size_t	i;

	new_array = malloc(new_size * sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array && array[i] && i < new_size - 1) {
		new_array[i] = array[i];
		i++;
	}
	new_array[new_size - 1] = NULL;
	free(array);
	return (new_array);
}

void process_pipe(t_minishell *shell, t_args **current_command, int *arg_count, int *redir_count)
{
    (*current_command)->is_pipe++;
    (*current_command)->args = realloc_array((*current_command)->args, *arg_count + 1);
    if (*redir_count > 0) {
        (*current_command)->redir = realloc_array((*current_command)->redir, *redir_count + 1);
        (*current_command)->is_redir = true;
    } else {
        (*current_command)->redir = realloc_array((*current_command)->redir, 1);
    }
    (*current_command)->args[*arg_count] = NULL;
    (*current_command)->redir[*redir_count] = NULL;

    *current_command = init_new_command();
    if (!(*current_command))
        return;
    add_command(shell, *current_command);
    *arg_count = 0;
    *redir_count = 0;
}

void process_redirections(t_args *current_command, char **args, int *i, int *redir_count)
{
    current_command->is_redir = true;
    if (!current_command->redir)
	{
        current_command->redir = realloc_array(current_command->redir, 1);
        *redir_count = 0;
    }
    while (args[*i])
	{
        current_command->redir = realloc_array(current_command->redir, *redir_count + 2);
        current_command->redir[(*redir_count)++] = ft_strdup(args[*i]);
        (*i)++;
    }
    current_command->redir[*redir_count] = NULL;
}

void process_argument(t_args *current_command, char *arg, int *arg_count)
{
    current_command->args = realloc_array(current_command->args, *arg_count + 2);
    current_command->args[(*arg_count)++] = ft_strdup(arg);
}

void handle_combined_cases(t_minishell *shell, t_args **current_command, char *arg, int *i, int *arg_count, int *redir_count)
{
    char *pipe_pos;
    char *redir_pos = ft_strchr(arg, '>') ? ft_strchr(arg, '>') : ft_strchr(arg, '<'); // refactor this //add << and >> 

	pipe_pos = ft_strchr(arg, '|');
    if (pipe_pos && redir_pos) {
        if (pipe_pos < redir_pos) {
            process_pipe(shell, current_command, arg_count, redir_count);
            process_redirections(*current_command, shell->args, i, redir_count);
        } else {
            process_redirections(*current_command, shell->args, i, redir_count);
            process_pipe(shell, current_command, arg_count, redir_count);
        }
    } else if (pipe_pos) {
        process_pipe(shell, current_command, arg_count, redir_count);
    } else if (redir_pos) {
        process_redirections(*current_command, shell->args, i, redir_count);
    }
}

void pipe_numeration(t_minishell *shell)
{
	t_args *tmp;
	int i;

	i = 0;
	tmp = shell->commands;
	while (tmp->next) 
	{
		i++;
		tmp = tmp->next;
	}
	tmp = shell->commands;
	while (tmp->next) 
	{
		tmp->is_pipe = i;
		i--;
		tmp = tmp->next;
	}
}
// last pushed version

// void	organize_struct(t_minishell *shell)
// {
// 	int	i;
// 	t_args *current_command;
// 	char	*arg;
// 	int arg_count;
//     int redir_count;

// 	i = 0;
// 	current_command = init_new_command();
// 	if (!current_command)
// 		return;
// 	add_command(shell, current_command);
// 	i = 0;
// 	arg_count = 0;
// 	redir_count = 0;
// 	while (shell->args[i]) {
// 		arg = shell->args[i];
// 		if (ft_strchr(arg, '|') || ft_strchr(arg, '>') || ft_strchr(arg, '<'))//add << and >> 
// 		{
// 			handle_combined_cases(shell, &current_command, arg, &i, &arg_count, &redir_count);
// 		} else {
// 			process_argument(current_command, arg, &arg_count);
// 		}
// 		i++;
// 	}
// 	current_command->args[arg_count] = NULL;
// 	if (current_command->redir)
// 		current_command->redir[redir_count] = NULL;
// 	pipe_numeration(shell);
// }


// ERROR: endless loop somwhere in the commented out code
//


// char **copy_array(char **dest, char **src, int len)
// {
// 	int i;

// 	i = 0;
// 	if (len == 0)
// 		return (NULL);
// 	dest = malloc((len + 1) * sizeof(char *));
// 	if (!dest)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		dest[i] = ft_strdup(src[i]);
// 		i++;
// 	}
// 	dest[i] = NULL;
// 	return (dest);
// }

// void	organize_struct(t_minishell *shell)
// {
// 	int	i;
// 	int k;
// 	t_args *current_command;
// 	int arg_count;
//     int redir_count;

// 	i = 0;
// 	k = 0;
// 	arg_count = 0;
// 	redir_count = 0;
// 	while (shell->args[i])
// 	{
// 		while (shell->args[k] == NULL 
// 			|| shell->args[k][0] == '|')
// 		{
// 			if (shell->args[k][0] == '>' || shell->args[k][0] == '<')
// 			{
// 				while (shell->args[k] == NULL 
// 					|| shell->args[k][0] == '|')
// 				{
// 					redir_count ++;
// 				}
// 			}
// 			else
// 				arg_count ++;
// 			k++;
// 		}
// 		current_command = init_new_command();
// 		if (!current_command)
// 			return;
// 		add_command(shell, current_command);
// 		if (arg_count > 0)
// 			current_command->args = copy_array(current_command->args, shell->args + i, arg_count);
// 		if (redir_count > 0)
// 		{
// 			current_command->redir = copy_array(current_command->redir, shell->args + i + arg_count, redir_count);
// 			current_command->is_redir = true;
// 		}
// 		if (shell->args[k] != NULL && ft_strchr(shell->args[k], '|'))
// 			k++;
// 		i = k;
// 	}
// 	pipe_numeration(shell);
// }

char **copy_array(char **dest, char **src, int len)
{
	int i;

	i = 0;
	if (len == 0)
		return (NULL);
	dest = malloc((len + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

char **organize_current_node(t_args *current_command, char **args)
{
	int len_args;
	int len_redir;

	len_args = 0;
	len_redir = 0;
	while (args[len_args] && !ft_strchr(args[len_args], '|'))
	{
		if (ft_strchr(args[len_args], '>') || ft_strchr(args[len_args], '<'))
		{
			len_redir ++;
			while (args[len_args + len_redir] && !ft_strchr(args[len_args + len_redir], '|'))
				len_redir++;
		}
		else
			len_args++;
	}
	if(len_args > 0)
		current_command->args = copy_array(current_command->args, args, len_args);
	if(len_redir > 0)
	{
		current_command->redir = copy_array(current_command->redir, args + len_args, len_redir);
		current_command->is_redir = true;
	}
	return (args + len_args + len_redir);
}

void	organize_struct(t_minishell *shell)
{
	char	**arg_tmp;
	t_args *current_command;

	arg_tmp = shell->args;
	while (arg_tmp)
	{
		current_command = init_new_command();
		if (!current_command)
			return;
		add_command(shell, current_command);
		while (arg_tmp && !ft_strchr(*arg_tmp, '|'))
		{
			arg_tmp = organize_current_node(current_command, arg_tmp);
		}
		if (arg_tmp && ft_strchr(*arg_tmp, '|'))
			arg_tmp++;
	}
	pipe_numeration(shell);
}