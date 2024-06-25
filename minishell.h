/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:48:02 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/25 20:23:03 by nandreev         ###   ########.fr       */
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

<<<<<<< HEAD
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
=======
void	init_environmentals(char **env, t_data *data);
// utils
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
>>>>>>> bfca0365fcb95ec64a8c607495198ad75dfcb49d
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
void	ft_bzero(void *s, size_t n);
int		ft_isdigit(int c);
// errors
void	args_error(void);
void	malloc_error(void);
void	unclosed_quote(void);
// execute
void	execute(char *str, t_data *data);
// builtins
void	mini_pwd(t_data *data);
int		mini_cd(t_data *data);
int		mini_env(t_data *data);
int		mini_unset(t_data *data, char *str);
// cleanup
void	free_everything(t_data *data);
void	free_array(char **array);


#endif