# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epresa-c <epresa-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 10:41:20 by epresa-c          #+#    #+#              #
#    Updated: 2022/08/10 13:37:36 by epresa-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c check_args.c utiles.c

OBJ = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
		CC $(CFLAGS) $(SRCS) -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
