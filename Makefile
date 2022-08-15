# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Emiliano <Emiliano@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/10 10:41:20 by epresa-c          #+#    #+#              #
#    Updated: 2022/08/13 10:39:19 by Emiliano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c check_args.c utiles.c print.c

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
