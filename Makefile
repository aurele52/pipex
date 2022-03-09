# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: audreyer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 22:50:22 by audreyer          #+#    #+#              #
#    Updated: 2022/03/09 18:34:51 by audreyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC_DIR = srcs/

SRC =  srcs/pipex.c

INC = includes/

LIBINC = ../libft/includes/

LIB = libft.a

BIN_DIR = bin/

BIN = pipex.o

CC = gcc

OPTS = -Wall -Werror -Wextra -g

all			:  $(NAME)

$(NAME)		: 
	make -C ../libft/
	$(CC) $(OPTS) -I $(LIBINC) -I includes/ -c $(SRC)
	$(CC) $(OPTS) $(BIN) -L ../libft/ -lft -o $(NAME)


clean 		:
	make clean -C ../libft/
	rm -f $(BIN)

fclean		: clean
	make fclean -C ../libft/
	rm -f $(NAME)

re			: fclean all 
