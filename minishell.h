/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:48:02 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/25 22:55:27 by nandreev         ###   ########.fr       */
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
void	parse_input(char *input, t_minishell *shell);


//utils
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);

// errors
void	args_error(void);
void	malloc_error(void);
void	unclosed_quote(void);

// free
void	free_args(t_minishell *shell);

#endif