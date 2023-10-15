#ifndef CUB3D_H
# define CUB3D_H

# include "math.h"
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "MLX42/include/MLX42/MLX42.h"

//fix: needs to be constant value
# define REDCOLOR 255 << 24 | 0 << 16 | 0 << 8 | 0xFF
# define BROWNCOLOR 165 << 24 | 42 << 16 | 42 << 8 | 0xFF
# define BLACKCOLOR 0 << 24 | 0 << 16 | 0 << 8 | 0xFF
# define GREENCOLOR 0 << 24 | 128 << 16 | 128 << 8 | 0xFF
# define LIGHTGREY 211 << 24 | 211 << 16 | 211 << 8 | 0xFF
# define GREYCOLOR 128 << 24 | 128 << 16 | 128 << 8 | 0xFF
# define YELLOWCOLOR 255 << 24 | 255 << 16 | 0 << 8 | 0xFF
# define BLUECOLOR 0 << 24 | 0 << 16 | 255 << 8 | 0xFF

# define NO_SIDE REDCOLOR
# define SO_SIDE YELLOWCOLOR
# define EA_SIDE BLUECOLOR
# define WE_SIDE GREENCOLOR

# define CEILING_COLOR LIGHTGREY
# define FLOOR_COLOR GREYCOLOR

typedef struct s_data {
	char	*addr;
	void	*img;
	void	*mlx;
	void	*mlx_win;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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
	double	ray_angle;
	double	ray_distance;
	bool	hitvertical;
	bool	down_ray;
	bool	up_ray;
	bool	right_ray;
	bool	left_ray;
}				t_rays;

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

typedef struct s_map {
	char	**map_grid;
	int		map_width;
	int		map_height;
}				t_map;

typedef struct s_player {
	t_textures		textures;
	t_map			map;
	t_mesurments	mes;
	t_data			img;
	t_rays			*ray;
	double			x;
	double			y;
	double			radius;
	int				turn_direction;
	int				walk_direction;
	int				side_direction;
	double			rotation_angle;
	double			moveSpeed;
	double			rotationSpeed;
}				t_player;

#endif
