/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:48:02 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/18 16:39:35 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifndef MAX_INPUT_SIZE //remove if not used
# define MAX_INPUT_SIZE 1024

typedef struct s_data
{
	char	**envs;
}	t_data;

typedef struct s_minishell
{
	char	**args;
}	t_minishell;


void	init_environmentals(char **env);

//utils
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);

// errors
void	args_error(void);
void	malloc_error(void);

#endif