# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 17:12:03 by lde-taey          #+#    #+#              #
#    Updated: 2024/09/20 14:36:36 by lde-taey         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Werror -Wall -Wextra

SRCS = main.c \
	init.c \
	utils.c \
	parse_input.c \
	parsing_preprocess.c \
	parsing_unfold.c \
	parsing_unfold_2.c \
	put_input_in_struct.c\
	parsing_utils.c \
	organize_redir_commands.c \
	check_cmd_valid.c \
	errors.c \
	errors_2.c \
	execute.c \
	execute_2.c \
	execute_3.c \
	cleanup.c \
	redirections.c \
	redirections_2.c \
	heredoc.c \
	pipe.c \
	builtins/mini_pwd.c \
	builtins/mini_cd.c \
	builtins/mini_env.c \
	builtins/mini_unset.c \
	builtins/mini_echo.c \
	builtins/mini_exit.c \
	builtins/mini_export.c \
	builtins/mini_export_2.c \
	signals.c \
	signals_handlers.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJS)  -L./libft -lft -lreadline -o $(NAME)

.PHONY : all clean fclean re

all : $(NAME)

clean :
	make clean -C ./libft
	rm -f $(OBJS)

fclean : clean
	make fclean -C ./libft
	rm -f $(NAME)

re : fclean all