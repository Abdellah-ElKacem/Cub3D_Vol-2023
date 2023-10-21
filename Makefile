NAME = cub3D

SRC = main.c \
	  get_next_line/get_next_line_utils.c \
	  get_next_line/get_next_line.c \
	  get_next_line/ft_strdup_gnl.c \
	  tools/ft_atoi.c \
	  tools/ft_isdigit.c \
	  tools/ft_strcmp.c \
	  tools/ft_strlen_fix.c \
	  parcing/colors_path_1.c \
	  parcing/colors_path.c \
	  parcing/creat_map.c \
	  parcing/parcing.c \
	  parcing/pars_map.c \
	  parcing/pars_utils.c \
	  parcing/path_player.c \


OBJ = ${SRC:.c=.o}

HEADER = cub3d.h

mlxa = ./MLX42/build/libmlx42.a

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -Ofast

all: mlxm ${NAME}

${NAME}: ${OBJ}
		${CC} ${CFLAGS} ${OBJ} ${mlxa} -lglfw -L"/Users/zel-kach/homebrew/opt/glfw/lib" -o $@

%.o: %.c ${HEADER}
		${CC} ${CFLAGS} -c $< -o $@

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
