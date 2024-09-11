#include "minishell.h"

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

int 	is_executable(t_minishell *shell, char *str)
{
	char	*tmp;
	char	*newcmd;
	int i;

	if(str == NULL || ft_strlen(str) == 0)
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
			{
				free(tmp);
				free(newcmd);
        		return (1);
			}
			i++;
			free(tmp);
			free(newcmd);
		}
	}
    return (0);
}

int 	is_path(char *str)
{
	if(str == NULL)
		return (0);
	if (ft_strchr(str, '/'))
		return (1);
	else
		return(0);
}

bool check_if_cmd_valid(t_minishell *shell, t_args *command)
{
	if (command == NULL)
		return (true);
	if ((command->args == NULL || command->args[0] == NULL )
		&& command->is_redir == 0 && command->is_pipe == 0)
	{
		//to be checked on school computer
		return (true);
	}
	else if (command->args == NULL && command->is_redir == 0 && command->is_pipe != 0)
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50); //to be checked on school computer
		return (false);
	}
	else if (command->args != NULL && (is_builtin(command->args[0]) 
		|| is_executable(shell, command->args[0])  
		|| is_path(command->args[0])))
		return (true);
	else if (command->is_redir == 1 && command->args == NULL)
		return (true);
	else
	{
		write(2, command->args[0], ft_strlen(command->args[0]));
		write(2, ": command not found\n", 20);
		return (false);
	}
}
