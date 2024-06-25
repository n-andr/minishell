# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-taey <lde-taey@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 17:12:03 by lde-taey          #+#    #+#              #
<<<<<<< HEAD
<<<<<<< HEAD
#    Updated: 2024/06/26 14:31:41 by lde-taey         ###   ########.fr        #
=======
#    Updated: 2024/06/21 15:25:02 by lde-taey         ###   ########.fr        #
>>>>>>> 4e1e255 (valgrind changes and relative path checking added to mini_cd)
=======
#    Updated: 2024/06/25 12:31:52 by lde-taey         ###   ########.fr        #
>>>>>>> d743376 (changes to other files)
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Werror -Wall -Wextra -g

<<<<<<< HEAD
SRCS = main.c init.c utils.c ft_split.c parse_input.c errors.c execute.c cleanup.c \
=======
SRCS = main.c init.c utils.c utils_2.c errors.c execute.c cleanup.c \
>>>>>>> 4e1e255 (valgrind changes and relative path checking added to mini_cd)
	builtins/mini_pwd.c \
	builtins/mini_cd.c \
	builtins/mini_env.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

.PHONY : all clean fclean re

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all