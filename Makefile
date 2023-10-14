# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 15:19:10 by ael-kace          #+#    #+#              #
#    Updated: 2023/10/14 17:13:57 by ael-kace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

HEADER = cub3d.h

SRC =	lib_tool/ft_strdup.c get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAG = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJ) 
	$(CC) $(CFLAG) $(OBJ) -o $(NAME) 

%.o : %.c $(HEADER)
	$(CC) $(CFLAG) -c $< -o $@

clean : 
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY = all clean fclean re