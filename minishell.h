/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:48:02 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/13 00:22:11 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

#ifndef MAX_INPUT_SIZE
# define MAX_INPUT_SIZE 1024

typedef struct s_args t_args;

typedef struct s_storefd
{
	int		stdin;
	int		stdout;
} t_storefd;

typedef struct s_args
{
	char 	**args;
	char 	**redir;
	bool	is_redir;
	bool	cmd_valid; //maybe not needed
	size_t	is_pipe;
	t_args	*next;
	t_args *previous;
	char	*heredoc;
	int		childpid;
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
	int		pid;
	int		fd_in;
	t_storefd	*fds;
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
void	malloc_error(t_minishell *shell);
void	unclosed_quote(void);
void	error_exec(void);
void	too_many_args_error(void);
int		pipe_error(void);
// parse
int		parse_input(char *input, t_minishell *shell);
void	unfold_input(t_minishell *shell);
void	unfold_struct(t_minishell *shell);
void	organize_struct(t_minishell *shell);
void	org_redir_commands(t_args *command);
char	**add_string_to_array(char **array, char *str);
bool	starts_with_char(char *str, char c);

//expantion
void	expand_command(t_minishell *shell, t_args *command);
// check
bool	check_if_cmd_valid(t_minishell *shell, t_args *command);
int		is_builtin(char *str);
int 	is_executable(t_minishell *shell, char *str);
int 	is_path(char *str);
// execute
void	execute(t_minishell *shell);
void	handle_cmd(t_minishell *shell, t_args *command);
int		handle_heredoc(t_args *command);
int		check_redirections(t_args *command);
int		redirection_loop(t_args *command);
void	save_fds(t_minishell *shell);
void	reset_fds(t_minishell *shell);
int		ft_pipe(t_minishell *shell); //, t_args *command);
int		scanifbuiltin(t_args *cmd);
int		execbuiltin(t_minishell *shell, t_args *cmd);
void	child_signals(void);
void	sigquit_handler(int sig);
void	single_cmd(t_minishell *shell, t_args *cmd);

// builtins
int		mini_pwd(t_minishell *shell);
int		mini_cd(t_minishell *shell, t_args *cmd);
int		mini_env(t_minishell *shell, t_args *cmd);
int		mini_unset(t_minishell *shell, t_args *cmd);
int		mini_echo(t_args *cmd);
int		mini_export(t_minishell *shell, t_args *cmd);
void	mini_exit(t_minishell *shell);
int		mini_export(t_minishell *shell, t_args *cmd);

// cleanup
void	free_everything(t_minishell *shell);
void	free_array(char **array);
void	free_commands(t_minishell *shell);
void	directory_check(t_minishell *shell, char *cmd);
void	command_check(t_minishell *shell, char *cmd);
// free
void	free_args(t_minishell *shell);

// tests
void	test_printf(t_minishell *shell); //delete
void	test_printf_command(t_args	*temp); //delete


#endif