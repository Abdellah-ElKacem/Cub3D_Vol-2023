NAME = cub3D

SRC = main.c

OBJ = ${SRC:.c=.o}

CC = cc

RM = rm -rf

CFLAGS = -Wall -Wextra -Ofast

all: ${NAME}

${NAME}: ${OBJ}
		 ${CC} ${CFLAGS} ${OBJ} MLX42/build/libmlx42.a -lglfw -L"/Users/zel-kach/homebrew/opt/glfw/lib" -o $@

%.o: %.c cub3D.h
		 ${CC} ${CFLAGS} -c $<

clean:
		${RM} ${OBJ}

fclean: clean
		${RM} ${NAME}

re: fclean all
