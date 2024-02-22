# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: audreyer <audreyer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/10 01:52:00 by audreyer          #+#    #+#              #
#    Updated: 2022/08/08 15:54:43 by audreyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#

FILE=	pipex.c	\
		pipex2.c	\
		exec.c

SRC_DIR = src/

SRC = $(addprefix $(SRC_DIR),$(FILE))

OBJ = $(SRC:.c=.o)

DOBJ		=	${SRC:.c=.d}

NAME = pipex

INC = include/pipex.h

CC = gcc

FLAGS		=	-g -Wall -Werror -Wextra -MMD

RM = rm -rf

all: $(NAME)

-include ${DOBJ}

.c.o:
			$(CC) $(FLAGS) -I include -c $< -o $(<:.c=.o)

$(NAME):	$(LIB) $(OBJ) $(INC) $(INC_LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME)

clean:
	${RM} $(OBJ) ${DOBJ}

fclean: clean
		$(RM) $(NAME)

re:		fclean all

INC_LIBFT = include/libft.h

LIB = $(SRC_DIR)libft.a

.PHONY: all clean fclean re .c.o
