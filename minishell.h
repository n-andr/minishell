/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:48:02 by nandreev          #+#    #+#             */
/*   Updated: 2024/09/28 02:09:49 by nandreev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stdbool.h>
# include <string.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# ifndef MAX_INPUT_SIZE
#  define MAX_INPUT_SIZE 1024
# endif

extern volatile int		g_sigint_received;

typedef struct s_args	t_args;

struct					s_termios;

typedef struct s_storefd
{
	int		stdin;
	int		stdout;
}	t_storefd;

typedef struct s_args
{
	char	**args;
	char	**redir;
	bool	is_redir;
	bool	cmd_valid;
	size_t	is_pipe;
	t_args	*next;
	t_args	*previous;
	char	*heredoc;
	int		childpid;
}	t_args;

typedef struct s_minishell
{
	char			**args;
	char			**envs;
	char			**paths;
	char			*pwd;
	char			*oldpwd;
	char			*home;
	int				exit_code;
	t_args			*commands;
	int				fd_in;
	t_storefd		*fds;
	struct termios	orig_termios;
	pid_t			pid[MAX_INPUT_SIZE];
}	t_minishell;

void	init_environmentals(char **env, t_minishell *shell);
// signals
void	signal_config_input(void);
void	sigint_handler_input(int sig);
void	signal_config_children(void);
void	signal_config_execute(void);
void	signal_config_heredoc(void);
void	sigint_handler_exec(int sig);
void	sigint_handler_children(int sig);
void	sigint_handler_heredoc(int sig);
void	sigquit_handler_children(int sig);
// utils
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *src);
// errors
void	args_error(void);
void	malloc_error(t_minishell *shell);
void	unclosed_quote(void);
void	error_exec(void);
void	too_many_args_error(void);
int		pipe_error(void);
// parse
int		parse_input(char *input, t_minishell *shell);
int		preprosess_string(char **input);
void	unfold_input(t_minishell *shell);
void	unfold_struct(t_minishell *shell);
void	organize_struct(t_minishell *shell);
void	org_redir_commands(t_args *command);
char	**add_string_to_array(char **array, char *str);
bool	starts_with_char(char *str, char c);
//expansion
void	expand_command(t_minishell *shell, t_args *command);
char	*unfold_double(char *str, int *i, t_minishell *shell);
char	*expand_variable(char *str, int *i, t_minishell *shell);
char	*free_and_assign(char *result, char *temp, char *substing);
char	*empty_result_check(char *result, char *arg);
char	*get_exit_code(t_minishell *shell, int *i);
bool	is_valid_name(char c, int *i);
// check
void	check_if_cmd_valid(t_minishell *shell, t_args *command);
int		is_builtin_or_path(char *str);
int		is_executable(t_minishell *shell, char *str);
int		is_path(char *str);
// execute
void	execute(t_minishell *shell);
void	handle_cmd(t_minishell *shell, t_args *command);
int		handle_heredoc(t_args *command, t_minishell *shell);
int		check_redirections(t_args *command);
int		redirection_loop(t_args *command);
int		syntax_error_check(t_args *command);
void	save_fds(t_minishell *shell);
void	reset_fds(t_minishell *shell);
int		ft_pipe(t_minishell *shell);
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
int		mini_exit(t_minishell *shell);
int		mini_export(t_minishell *shell, t_args *cmd);
int		add_var(char *arg, int name_len, t_minishell *shell);
int		var_exists(char *arg, int name_len, char *new_var, t_minishell *shell);
void	create_paths(t_minishell *shell);
char	**realloc_env_array(char **envs, char *new_var);
int		where_is_equalsign(char *str);
char	**sort_alphabetically(char **envs);
// cleanup
void	free_everything(t_minishell *shell);
void	free_array(char **array);
void	free_commands(t_minishell *shell);
void	directory_check(t_minishell *shell, char *cmd);
void	command_check(t_minishell *shell, char *cmd);

#endif