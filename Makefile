# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 15:19:10 by ael-kace          #+#    #+#              #
#    Updated: 2023/10/17 17:23:12 by ael-kace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

HEADER = cub3d.h

SRC =	cub_main.c \
		lib_tool/ft_strdup_gnl.c lib_tool/ft_atoi.c \
		lib_tool/ft_isdigit.c \
		g_n_l/get_next_line.c g_n_l/get_next_line_utils.c 

OBJ = $(SRC:.c=.o)

CC = cc

CFLAG = -Wall -Werror -Wextra -g #-fsanitize=address

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