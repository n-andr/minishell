#include "minishell.h"


int	array_len(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

// char	**keep_redir(char **redir)
// {
// 	int i;
// 	char	**new_redir;
// 	i = 0;
// 	new_redir = NULL;
// 	if (redir == NULL || redir[i] == NULL)
// 		return (NULL);
// 	else
// 		i++;
// 	while (redir[i] != NULL 
// 		&& (ft_strchr(redir[i], '>') || ft_strchr(redir[i], '<') 
// 		|| ft_strchr(redir[i - 1], '<') || ft_strchr(redir[i - 1], '>')))
// 		i++;
// 	new_redir = copy_array(new_redir, redir, i);
// 	return (new_redir);
// }

// void	builtins_redirs(t_args *command)
// {
// 	int i;
// 	int a_len;
// 	int args_from_redir;
// 	char	**new_args;
// 	char	**new_redir;

// 	i = 0;
// 	new_args = NULL;
// 	new_redir = NULL;	
// 	a_len = array_len(command->args);
// 	new_redir =  keep_redir(command->redir);
// 	args_from_redir = array_len(command->redir) - array_len(new_redir);
// 	if (args_from_redir > 0)
// 	{
// 		new_args = malloc((a_len + args_from_redir + 1) * sizeof(char *));
// 		if (!new_args)
// 			return;
// 		while (command->args[i] != NULL)
// 		{
// 			new_args[i] = ft_strdup(command->args[i]);
// 			i++;
// 		}
// 		i = array_len(new_redir);
// 		while (command->redir[i] != NULL)
// 		{
// 			new_args[a_len] = ft_strdup(command->redir[i]);
// 			i++;
// 			a_len++;
// 		}
// 		new_args[a_len] = NULL;
// 		free_array(command->args);
// 		free_array(command->redir);
// 		command->args = new_args;
// 		command->redir = new_redir;
// 	}
// 	else
// 	{
// 		free_array(new_redir);
// 	}
// }

char	**add_string_to_array(char **array, char *str)
{
	int	i;
	int	len;
	char	**new_array;

	i = 0;
	len = array_len(array);
	new_array = malloc((len + 2) * sizeof(char *));
	if (!new_array)
		return (NULL);
	while (i < len)
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = ft_strdup(str);
	new_array[i + 1] = NULL;
	free_array(array);
	return (new_array);
}

// void	org_redir_commands(t_args *command)
// {
// 	char **new_redir;
// 	int i;

// 	new_redir = NULL;
// 	i = 0;
// 	if (command->redir == NULL || command->redir[i] == NULL)
// 		return;
// 	if (starts_with_char(command->redir[i], '>') || starts_with_char(command->redir[i], '<'))
// 	{
// 		new_redir = add_string_to_array(new_redir, command->redir[i]);
// 		i++;
// 	}
// 	while (command->redir[i] != NULL)
// 	{
// 		if ((starts_with_char(command->redir[i], '>') || starts_with_char(command->redir[i], '<') 
// 		|| starts_with_char(command->redir[i - 1], '>') || starts_with_char(command->redir[i - 1], '<')))
// 		{
// 			new_redir = add_string_to_array(new_redir, command->redir[i]);
// 		}
// 		else
// 		{
// 			command->args = add_string_to_array(command->args, command->redir[i]);
// 		}
// 		i++;
// 	}
// 	free_array(command->redir);
// 	command->redir = new_redir;
// }
