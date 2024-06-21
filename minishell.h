/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:48:02 by nandreev          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/26 14:43:53 by lde-taey         ###   ########.fr       */
=======
/*   Updated: 2024/06/21 15:44:08 by lde-taey         ###   ########.fr       */
>>>>>>> 4e1e255 (valgrind changes and relative path checking added to mini_cd)
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
	char	*pwd;
	char	*oldpwd;
	char	*home;
	char	*cmd;
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


void	init_environmentals(char **env, t_data *data);
// utils
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);


// errors
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
// errors
void	args_error(void);
void	malloc_error(void);
// execute
void	execute(char *str, t_data *data);
// builtins
void	mini_pwd(t_data *data);
int		mini_cd(t_data *data);
// cleanup
void free_everything(t_data *data);

#endif