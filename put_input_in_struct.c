/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_input_in_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:05:17 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/11 19:33:28 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*init_new_command(void)
{
	t_args	*new_command;

	new_command = malloc(sizeof(t_args));
	if (!new_command)
		return (NULL);
	new_command->args = NULL;
	new_command->redir = NULL;
	new_command->is_redir = false;
	new_command->cmd_valid = false; //maybe not needed
	new_command->is_pipe = 0;
	new_command->heredoc = NULL;
	new_command->previous = NULL;
	new_command->next = NULL;
	return (new_command);
}

void	add_command(t_minishell *shell, t_args *new_command)
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
		new_command->previous = current;
	}
}

void	pipe_numeration(t_minishell *shell)
{
	t_args	*tmp;
	int		i;

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

char	**copy_array(char **dest, char **src, int len)
{
	int	i;

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

bool	starts_with_char(char *str, char c)
{
	if (!str || !str[0])
		return (false);
	if (str[0] == c)
		return (true);
	return (false);
}

// char	**organize_current_node(t_args *current_command, char **args)
// {
// 	int	len_args;
// 	int	len_redir;

// 	len_args = 0;
// 	len_redir = 0;
	
// 	while (args[len_args]
// 		&& !starts_with_char(args[len_args], '|')
// 		&& !starts_with_char(args[len_args], '>')
// 		&& !starts_with_char(args[len_args], '<'))
// 		len_args++;
// 	while (args[len_args + len_redir]
// 		&& !starts_with_char(args[len_args + len_redir], '|'))
// 		len_redir++;
// 	if (len_args > 0)
// 		current_command->args = copy_array(current_command->args, args, len_args);
// 	if (len_redir > 0)
// 	{
// 		current_command->redir = copy_array(current_command->redir, args + len_args, len_redir);
// 		current_command->is_redir = true;
// 	}
// 	org_redir_commands(current_command);
// 	return (args + len_args + len_redir);
// }

char	**organize_current_node(t_args *command, char **args)
{
	int	len;

	len = 0;
	while (args[len] && !starts_with_char(args[len], '|'))
	{
		if (starts_with_char(args[len], '>') 
			|| starts_with_char(args[len], '<'))
		{
			command->redir = add_string_to_array(command->redir, args[len]);
		}
		else if (len > 0 && (starts_with_char(args[len - 1], '>') || starts_with_char(args[len - 1], '<')))
		{
			command->redir = add_string_to_array(command->redir, args[len]);
		}
		else
		{
			command->args = add_string_to_array(command->args, args[len]);
		}
		len++;
	}
	if (command->redir != NULL && command->redir[0] != NULL)
		command->is_redir = true;
	//org_redir_commands(current_command);
	return (args + len);
}

void	organize_struct(t_minishell *shell)
{
	char	**arg_tmp;
	t_args	*current_command;

	arg_tmp = shell->args;
	while (arg_tmp && *arg_tmp)
	{
		current_command = init_new_command();
		if (!current_command)
			return ;
		add_command(shell, current_command);
		while (*arg_tmp && !starts_with_char(*arg_tmp, '|'))
		{
			arg_tmp = organize_current_node(current_command, arg_tmp);
		}
		if (*arg_tmp && starts_with_char(*arg_tmp, '|'))
			arg_tmp++;
	}
	pipe_numeration(shell);
}
