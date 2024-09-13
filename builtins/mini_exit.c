/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:09:29 by lde-taey          #+#    #+#             */
/*   Updated: 2024/09/13 17:20:02 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_number(char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = "minishell: exit: numeric argument required";
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
	}
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0)
		{
			ft_putendl_fd(s, STDERR_FILENO);
			return (2);
		}
		i++;
	}
	return (ft_atoi(str));
}

void	mini_exit(t_minishell *shell)
{
	int	exit_code;

	exit_code = 0;
	printf("exit\n");
	if (shell->commands->args[1] == NULL)
	{
		exit_code = 0;
	}
	else if (shell->commands->args[2] == NULL)
	{
		exit_code = check_if_number(shell->commands->args[1]);
	}
	else
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		exit_code = 1;
	}
	free_everything(shell);
	exit(exit_code);
}
