# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlaine <vlaine@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 18:25:17 by raho              #+#    #+#              #
#    Updated: 2022/02/17 17:13:28 by vlaine           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
CC = gcc
LIB = libft/libft.a
INCLUDE = libft/
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c copy_tetriminos.c check_errors.c move_tetriminos.c\
	create_square.c solve_square.c free_all.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS) $(LIB) $(INCLUDE)
	$(CC) $(CFLAGS) $(SRCS) $(LIB) -I $(INCLUDE) -o $(NAME)

$(LIB):
	make -C libft

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
