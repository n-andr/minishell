/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:48:02 by nandreev          #+#    #+#             */
/*   Updated: 2024/08/20 00:54:24 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

#ifndef MAX_INPUT_SIZE
# define MAX_INPUT_SIZE 1024

typedef struct s_args t_args;

typedef struct s_args
{
	char 	**args;
	char 	**redir;
	bool	is_redir;
	size_t	is_pipe;
	t_args	*next;
	char	*heredoc;
}	t_args;

typedef struct s_minishell
{
	char	**args;
	char	**envs;
	char	**paths;
	char	*pwd;
	char	*oldpwd;
	char	*home;
	int		exit_code;
	t_args	*commands;
}	t_minishell;

void	init_environmentals(char **env,t_minishell *shell);
void	signal_config(void);
// utils
/* char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s); */
int		ft_strcmp(const char *s1, const char *s2); /*
int		ft_strncmp(const char *s1, const char *s2, size_t n); */
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
/*void	ft_bzero(void *s, size_t n);
int		ft_isdigit(int c); */
// errors
void	args_error(void);
void	malloc_error(void);
void	unclosed_quote(void);
void	error_exec(void);
// parse
int	parse_input(char *input, t_minishell *shell);
void	unfold_input(t_minishell *shell);
//void	unfold_struct(t_minishell *shell);
void	organize_struct(t_minishell *shell);
// execute
int		execute(t_minishell *shell);
int		handle_cmd(t_minishell *shell, t_args *command);
int		handle_heredoc(t_minishell *shell);
int		check_redirections(t_args *command);
int		ft_pipe(t_minishell *shell); //, t_args *command);
// builtins
void	mini_pwd(t_minishell *shell);
int		mini_cd(t_minishell *shell);
int		mini_env(t_minishell *shell);
int		mini_unset(t_minishell *shell, char *str);
void	mini_echo(t_minishell *shell);
void	mini_exit(t_minishell *shell);

// cleanup
void	free_everything(t_minishell *shell);
void	free_array(char **array);
void	free_commans(t_minishell *shell);
// free
void	free_args(t_minishell *shell);

// tests
void test_printf(t_minishell *shell); //delete


#endif