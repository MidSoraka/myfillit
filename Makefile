# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omistaja <omistaja@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/04 18:25:17 by raho              #+#    #+#              #
#    Updated: 2022/02/11 16:50:12 by raho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c copy_tetriminos.c check_errors.c move_tetriminos.c create_square.c solve_square.c free_all.c

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -L./libft -lft

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
