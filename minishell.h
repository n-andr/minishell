/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:48:02 by nandreev          #+#    #+#             */
/*   Updated: 2024/06/20 19:43:37 by lde-taey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#ifndef MAX_INPUT_SIZE
# define MAX_INPUT_SIZE 1024

typedef struct s_data
{
	char	**envs;
	char	*pwd;
	char	*oldpwd;
	char	*home;
	char	*cmd;
}	t_data;

void	init_environmentals(char **env, t_data *data);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// errors
void	args_error(void);
void	malloc_error(void);
// execute
void	execute(char *str, t_data *data);
// builtins
void	mini_pwd(t_data *data);
void	mini_cd(t_data *data);
// cleanup
void free_everything(t_data *data);

#endif