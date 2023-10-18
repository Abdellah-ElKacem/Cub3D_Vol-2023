NAME = cub3D

SRC = main.c

OBJ = ${SRC:.c=.o}

HEADER = cub3d.h

mlxa = ./MLX42/build/libmlx42.a

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Ofast

all: mlxm ${NAME}

${NAME}: ${OBJ}
		${CC} ${CFLAGS} ${OBJ} ${mlxa} -lglfw -L"/Users/zel-kach/homebrew/opt/glfw/lib" -o $@

%.o: %.c ${HEADER} ${libfta}
		${CC} ${CFLAGS} -c $<

mlxm:
		make -C MLX42/build

mlxclean:
			make clean -C MLX42/build

mlxfclean:
			make fclean -C MLX42/build

clean: mlxclean
		${RM} ${OBJ}

fclean: clean
		${RM} ${NAME}

re: fclean all
