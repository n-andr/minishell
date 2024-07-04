# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nandreev <nandreev@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 17:12:03 by lde-taey          #+#    #+#              #
#    Updated: 2024/06/30 22:56:07 by nandreev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Werror -Wall -Wextra -g

SRCS = main.c \
	init.c \
	utils.c \
	utils_2.c \
	ft_split.c \
	parse_input.c \
	errors.c \
	execute.c \
	cleanup.c \
	redirections.c \
	builtins/mini_pwd.c \
	builtins/mini_cd.c \
	builtins/mini_env.c \
	builtins/mini_unset.c \
	#builtins/mini_echo.c \	

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -lreadline libft/libft.a -o $(NAME)

.PHONY : all clean fclean re

all : $(NAME)

clean :
	make clean -C ./libft
	rm -f $(OBJS)

fclean : clean
	make fclean -C ./libft
	rm -f $(NAME)

re : fclean all