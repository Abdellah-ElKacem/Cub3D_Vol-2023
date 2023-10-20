
#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_colors {
	int		ceiling_color;
	int		floor_color;
	int		red;
	int		green;
	int		grey;
	int		black;
	int		yellow;
}				t_colors;

typedef struct s_data {
	int		bits_per_pixel;
	int		endian;
	int		line_length;
	char	*addr;
	void	*img;
	void	*mlx;
	void	*mlx_win;
}				t_data;

typedef struct s_textures {
	int	**no_side;
	int	**ea_side;
	int	**so_side;
	int	**we_side;
}				t_textures;

typedef struct s_rays {
	int		x;
	int		y;
	bool	hitvertical;
	bool	down_ray;
	bool	up_ray;
	bool	right_ray;
	bool	left_ray;
	double	ray_angle;
	double	ray_distance;
}				t_rays;

typedef struct s_rgba
{
	int	r;
	int	g;
	int	b;
}				t_rgba;

typedef struct s_map
{
	int		map_height;
	int		map_width;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_rgba	f;
	t_rgba	c;
}				t_map;

typedef struct s_mesurments {
	int		tile_size;
	int		map_num_rows;
	int		map_num_colms;
	int		win_width;
	int		win_height;
	int		num_rays;
	int		wall_strip_width;
	int		wall_hitx;
	int		wall_hity;
	double	fov_angle;
	double	mini_map_scale;
	double	wall_distance;
}				t_mesurments;

typedef struct s_player {
	t_colors		color;
	t_textures		textures;
	t_map			map;
	t_mesurments	mes;
	t_data			img;
	t_rays			*ray;
	int				turn_direction;
	int				walk_direction;
	int				side_direction;
	double			x;
	double			y;
	double			radius;
	double			rotation_angle;
	double			move_speed;
	double			rotation_speed;
}				t_player;

size_t	ft_strlen(char *s);
char	*ft_strdup_plus(const char *s1, int len, int start, int *end);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup_gnl(const char *s1);
char	*ft_strdup(char *s1);
char	*get_next_line(int fd);
void	parcing(t_player *player, char **av);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_atoi(const char *str);
int		ft_strchr(const char *s, char c);

#endif
