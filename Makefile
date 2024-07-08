# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 17:12:03 by lde-taey          #+#    #+#              #
#    Updated: 2024/07/08 01:44:57 by nandreev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Werror -Wall -Wextra

SRCS = main.c \
	init.c \
	utils.c \
	utils_2.c \
	parse_input.c \
	parsing_unfold.c\
	put_input_in_struct.c\
	errors.c \
	cleanup.c \
	redirections.c \
	heredoc.c \
	free.c \
	builtins/mini_pwd.c \
	builtins/mini_cd.c \
	builtins/mini_env.c \
	builtins/mini_unset.c \

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