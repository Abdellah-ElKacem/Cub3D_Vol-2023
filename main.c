#include "cub3D.h"

char	map[11][15] = {
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1},
			{1, 0, 0, 1, 0, 0, 1, 2, 2, 2, 2, 1, 0, 0, 1},
			{1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1},
			{1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
			{1, 0, 0, 0, 0, 1, 0, 0, 'N', 0, 0, 1, 0, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void	draw_line(t_player *player, double x, double y, double x1, double y1)
{
	int		steps;
	double	x_increment;
	double	y_increment;

	if (fabs(x1 - x) > fabs(y1 - y))
		steps = fabs(x1 - x);
	else
		steps = fabs(y1 - y);
	x_increment = (x1 - x) / (double)steps;
	y_increment = (y1 - y) / (double)steps;
	while (steps--)
	{
		mlx_put_pixel(player->img.img, x * player->mes.mini_map_scale, y * player->mes.mini_map_scale, YELLOWCOLOR);
		x += x_increment;
		y += y_increment;
	}
}

int	texture_mapping(t_player *player, int **texture, int y, int y1, double wall_strip_height, int i)
{
	int	pixel_x;
	int	pixel_y;

	if (player->ray[i].hitvertical)
		pixel_x = fmod(player->ray[i].y, 64);
	else
		pixel_x = fmod(player->ray[i].x, 64);
	pixel_y = y - y1;
	pixel_y *=  (64 / wall_strip_height);
	if (pixel_y >= 64)
		pixel_y = 63;
	return (texture[pixel_y][pixel_x]);
}

void draw_rectangles(t_player *player, int x, double wall_strip_height, int i, int **texture)
{
	int	y;
	int	y1;

	y1 = (player->mes.win_height / 2) - (wall_strip_height / 2);
	y = -1;
	while (++y < player->mes.win_height)
	{
		if (y < y1)
			mlx_put_pixel(player->img.img, x, y, CEILING_COLOR);
		else if (y < y1 + wall_strip_height)
			mlx_put_pixel(player->img.img, x, y, texture_mapping(player, texture, y, y1, wall_strip_height, i));
		else
			mlx_put_pixel(player->img.img, x, y, FLOOR_COLOR);
	}
}

double distance_between_points(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void	draw_rays(t_player *player)
{
	int i;

	i = -1;
	while (++i < player->mes.num_rays)
		draw_line(player, player->x , player->y, player->ray[i].x, player->ray[i].y);
}

int has_wall(t_player *player, double x, double y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (x < 0 || x > player->mes.win_width || y < 0 || y > player->mes.win_height)
		return (1);
	i = floor(y / player->mes.tile_size);
	j = floor(x / player->mes.tile_size);
	if (i >= 11 || j >= 15)
		return (1);
	return (map[i][j] == 1); //replaye with player->map.map_grid
}

void	cast(t_player *player, int i)
{
	double	xstep;
	double	ystep;
	double	xintercept;
	double	yintercept;
	int	hor_wall_hit_x = 0;
	int	hor_wall_hit_y = 0; 
	yintercept = floor(player->y / player->mes.tile_size) * player->mes.tile_size;
	yintercept += player->ray[i].down_ray ? player->mes.tile_size : 0; 
	xintercept = player->x + ((yintercept - player->y) / tan(player->ray[i].ray_angle));
	ystep = player->mes.tile_size;
	ystep *= player->ray[i].up_ray ? -1 : 1;
	xstep =  player->mes.tile_size / tan(player->ray[i].ray_angle);
	xstep *= (player->ray[i].left_ray && xstep > 0) ? -1 : 1;
	xstep *= (player->ray[i].right_ray && xstep < 0) ? -1 : 1;
	while (1)
	{
		if (has_wall(player, xintercept, yintercept - (player->ray[i].up_ray ? 1 : 0)))
		{
			hor_wall_hit_x = xintercept;
			hor_wall_hit_y = yintercept;
			break ;
		}
		else
		{
			xintercept += xstep;
			yintercept += ystep;
		}
	}

	//vertical
	player->ray[i].hitvertical = false;
	int	ver_wall_hit_x = 0;
	int	ver_wall_hit_y = 0; 
	xintercept = floor(player->x / player->mes.tile_size) * player->mes.tile_size;
	xintercept += player->ray[i].right_ray ? player->mes.tile_size : 0;
	yintercept = player->y + ((xintercept - player->x) * tan(player->ray[i].ray_angle));
	xstep = player->mes.tile_size;
	xstep *= player->ray[i].left_ray ? -1 : 1;
	ystep = player->mes.tile_size * tan(player->ray[i].ray_angle);
	ystep *= (player->ray[i].up_ray && ystep > 0) ? -1 : 1;
	ystep *= (player->ray[i].down_ray && ystep < 0) ? -1 : 1;
	while (1)
	{
		if (has_wall(player, xintercept - (player->ray[i].left_ray ? 1 : 0), yintercept))
		{
			ver_wall_hit_x = xintercept;
			ver_wall_hit_y = yintercept;
			break ;
		}
		else
		{
			xintercept += xstep;
			yintercept += ystep;
		}
	}

	double hor_distance = distance_between_points(player->x, player->y, hor_wall_hit_x, hor_wall_hit_y);
	double ver_distance = distance_between_points(player->x, player->y, ver_wall_hit_x, ver_wall_hit_y);

	if (hor_distance < ver_distance)
	{
		player->ray[i].x = hor_wall_hit_x;
		player->ray[i].y = hor_wall_hit_y;
		player->ray[i].hitvertical = false;
	}
	else
	{
		player->ray[i].x = ver_wall_hit_x;
		player->ray[i].y = ver_wall_hit_y;
		player->ray[i].hitvertical = true;
	}
	player->ray[i].ray_distance = sqrt(pow(player->ray[i].x - player->x, 2) + pow(player->ray[i].y - player->y, 2));
}

void	cast_settings(t_player *player, int i)
{
	player->ray[i].ray_angle = fmod(player->ray[i].ray_angle, 2 * M_PI);
	if (player->ray[i].ray_angle < 0)
		player->ray[i].ray_angle = (2 * M_PI) + player->ray[i].ray_angle;
	player->ray[i].down_ray = player->ray[i].ray_angle < M_PI;
	player->ray[i].right_ray = player->ray[i].ray_angle < (0.5 * M_PI) || player->ray[i].ray_angle > (1.5 * M_PI);
	player->ray[i].up_ray = !player->ray[i].down_ray;
	player->ray[i].left_ray = !player->ray[i].right_ray;
}

void clear_win(t_player *player)
{
	if (player->img.img)
		mlx_delete_image(player->img.mlx, player->img.img);
	player->img.img = mlx_new_image(player->img.mlx, player->mes.win_width, player->mes.win_height);
}

void	cast_all_rays(t_player *player)
{
	double	ray_angle;
	double	angle_increment;
	int		i;

	i = -1;
	clear_win(player);
	ray_angle = player->rotation_angle - (player->mes.fov_angle / 2);
	angle_increment = player->mes.fov_angle / player->mes.num_rays;;
	while (++i < player->mes.num_rays)
	{
		player->ray[i].ray_angle = ray_angle;
		cast_settings(player, i);
		cast(player, i);
		ray_angle += angle_increment;
	}
}

void draw_mini_square(t_player *player, int x, int y, int Color)
{
	int	i;
	int	j;
	int	dy;
	int	dx;

	i = x * 64 * player->mes.mini_map_scale;
	j = y * 64 * player->mes.mini_map_scale;
	dy = -1;
	while (++dy < player->mes.tile_size * player->mes.mini_map_scale)
	{
		dx = -1;
		while (++dx < player->mes.tile_size * player->mes.mini_map_scale)
			mlx_put_pixel(player->img.img, i + dx, j + dy, Color);
	}
}

void	render_projected_walls(t_player *player)
{
	double	correctDistance;
	double	distanceProjectionPlane;
	double	wall_strip_height;
	int		i;
	int		**texture;

	distanceProjectionPlane = (player->mes.win_width / 2) / tan(player->mes.fov_angle / 2);
	i = -1;
	while (++i < player->mes.num_rays)
	{
		correctDistance = player->ray[i].ray_distance * cos(player->rotation_angle - player->ray[i].ray_angle);
		wall_strip_height = (player->mes.tile_size / correctDistance) * (distanceProjectionPlane);
		if (player->ray[i].hitvertical && player->ray[i].right_ray)
			texture = player->textures.ea_side;
		else if (player->ray[i].hitvertical && player->ray[i].left_ray)
			texture = player->textures.we_side;
		else if (!player->ray[i].hitvertical && player->ray[i].up_ray)
			texture = player->textures.no_side;
		else if (!player->ray[i].hitvertical && player->ray[i].down_ray)
			texture = player->textures.so_side;
		draw_rectangles(player, i, wall_strip_height,i , texture);
	}
}

void draw_mini_map(t_player *player)
{
	int	x;
	int	y = -1;

	while (++y < 11)
	{
		x = -1;
		while (++x < 15)
		{
			if (map[y][x] == 1) //replaye with player->map.map_grid
				draw_mini_square(player, x, y, REDCOLOR);
			else if (map[y][x] == 2) //replaye with player->map.map_grid
				draw_mini_square(player, x, y, BLACKCOLOR);
			else
				draw_mini_square(player, x, y, GREYCOLOR);
		}
	}
}

void	draw_player(t_player *player)
{
	int	x;
	int	y;
	int	move_step;
//check for collision on the sides*********************
	player->rotation_angle += player->turn_direction * player->rotationSpeed;
	move_step = player->moveSpeed * player->walk_direction;
	if (has_wall(player, player->x + cos(player->rotation_angle) * move_step, player->y + sin(player->rotation_angle) * move_step))
		return ;
	player->x += cos(player->rotation_angle) * move_step;
	player->y += sin(player->rotation_angle) * move_step;
	if (player->side_direction == 1)
	{
		player->x += cos(player->rotation_angle - M_PI / 2) * player->moveSpeed;
		player->y += sin(player->rotation_angle - M_PI / 2) * player->moveSpeed;
	}
	else if (player->side_direction == -1)
	{
		player->x += cos(player->rotation_angle + M_PI / 2) * player->moveSpeed;
		player->y += sin(player->rotation_angle + M_PI / 2) * player->moveSpeed;
	}
	cast_all_rays(player);
	render_projected_walls(player);
	draw_mini_map(player);
	y = -10;
	while (++y < 10)
	{
		x = -10;
		while (++x < 10)
		{
			int draw_x = player->x + x;
			int draw_y = player->y + y;
			draw_x *= player->mes.mini_map_scale;
			draw_y *= player->mes.mini_map_scale;
			mlx_put_pixel(player->img.img, draw_x, draw_y, GREENCOLOR);
		}
	}
}

void	find_neemo(t_player *player)
{
	int	x;
	int	y;

	x = -1;
	while (++x < player->mes.map_num_rows)
	{
		y = -1;
		while (++y < player->mes.map_num_colms)
		{
			if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E' || map[x][y] == 'W')
			{
				player->x = y * player->mes.tile_size;
				player->y = x * player->mes.tile_size;
				if (map[x][y] == 'N')
					player->rotation_angle = M_PI * 1.5;
				else if (map[x][y] == 'S')
					player->rotation_angle = M_PI / 2;
				else if (map[x][y] == 'E')
					player->rotation_angle = 0;
				else if (map[x][y] == 'W')
					player->rotation_angle = M_PI;
				return ;
			}
		}
	}
}

void	init_player(t_player *player)
{
	player->turn_direction = 0;
	player->walk_direction = 0;
	player->side_direction = 0;
	player->moveSpeed = 1.0;
	player->rotationSpeed = 2 * (M_PI / 180);
	find_neemo(player);
}

void	init_mesurments(t_player *player)
{
	// player->map.map_grid = map;
	// player->map.map_width = tmp_map_width from get_next_line;
	// player->map.map_height = tmp_map_height from get_next_line;
	player->mes.tile_size = 64;
	player->mes.map_num_rows = 11; /*replace with player->map.map_width*/
	player->mes.map_num_colms = 15; /*replace with player->map.map_height*/
	player->mes.win_width = player->mes.map_num_colms * player->mes.tile_size;
	player->mes.win_height = player->mes.map_num_rows * player->mes.tile_size;
	player->mes.fov_angle = 60 * (M_PI / 180);
	player->mes.wall_strip_width = 1;
	player->mes.num_rays = player->mes.win_width / player->mes.wall_strip_width;
	player->mes.mini_map_scale = 0.2;
	player->ray = malloc(player->mes.num_rays * sizeof(t_rays));
}

void	key_right(t_player *player, mlx_key_data_t keydata)
{
	if (keydata.action == MLX_PRESS)
		player->turn_direction = 1;
	else if (keydata.action == MLX_RELEASE)
		player->turn_direction = 0;
}

void	key_left(t_player *player, mlx_key_data_t keydata)
{
	if (keydata.action == MLX_PRESS)
		player->turn_direction = -1;
	else if (keydata.action == MLX_RELEASE)
		player->turn_direction = 0;
}
void	key_w(t_player *player, mlx_key_data_t keydata)
{
	if (keydata.action == MLX_PRESS)
		player->walk_direction = 1;
	else if (keydata.action == MLX_RELEASE)
		player->walk_direction = 0;
}
void	key_s(t_player *player, mlx_key_data_t keydata)
{
	if (keydata.action == MLX_PRESS)
		player->walk_direction = -1;
	else if (keydata.action == MLX_RELEASE)
		player->walk_direction = 0;
}

void	key_a(t_player *player, mlx_key_data_t keydata)
{
	if (keydata.action == MLX_PRESS)
		player->side_direction = 1;
	else if (keydata.action == MLX_RELEASE)
		player->side_direction = 0;
}

void	key_d(t_player *player, mlx_key_data_t keydata)
{
	if (keydata.action == MLX_PRESS)
		player->side_direction = -1;
	else if (keydata.action == MLX_RELEASE)
		player->side_direction = 0;
}

void	key_func(mlx_key_data_t keydata, void *param)
{
	t_player	*player;

	player = param;
	if (keydata.key == MLX_KEY_W)
		key_w(player, keydata);
	if (keydata.key == MLX_KEY_S)
		key_s(player, keydata);
	if (keydata.key == MLX_KEY_LEFT)
		key_left(player, keydata);
	if (keydata.key == MLX_KEY_RIGHT)
		key_right(player, keydata);
	if (keydata.key == MLX_KEY_A)
		key_a(player, keydata);
	if (keydata.key == MLX_KEY_D)
		key_d(player, keydata);
	if (keydata.key == MLX_KEY_ESCAPE)
		exit (0);
}

void	loop(void *d)
{
	t_player	*player;

	player = (t_player *)d;
	draw_player(player);
	draw_rays(player);
	mlx_image_to_window(player->img.mlx, player->img.img, 0, 0);
}

int	**fill_color_array(mlx_texture_t *side)
{
	int	y;
	int	x;
	int	combined;
	int **pixel_holder;
	int pixel = 0;

	combined = 0;
	pixel_holder = (int **)malloc(64 * sizeof(int *));
	y = -1;
	while (++y < 64)
		pixel_holder[y] = (int *)malloc(sizeof(int) * 64);
	y = -1;
	while (++y < 64)
	{
		x = -1;
		while (++x < 64)
		{
			combined = (side->pixels[pixel] << 24) | (side->pixels[pixel + 1] << 16)
						| (side->pixels[pixel + 2] << 8) | side->pixels[pixel + 3];
			pixel_holder[y][x] = combined;
			pixel += 4;
		}
	}
	return (pixel_holder);
}

//south side is broken ?
void	init_textures(t_player *player)
{
	mlx_texture_t *no_side = mlx_load_png("./png_files/redbrick.png");
	player->textures.no_side = fill_color_array(no_side);
	mlx_texture_t *ea_side = mlx_load_png("./png_files/brownbrick.png");
	player->textures.ea_side = fill_color_array(ea_side);
	mlx_texture_t *so_side = mlx_load_png("./png_files/coal.png");
	player->textures.so_side = fill_color_array(so_side);
	mlx_texture_t *we_side = mlx_load_png("./png_files/planks.png");
	player->textures.we_side = fill_color_array(we_side);
}

int	main()
{
	t_player		player;

	init_mesurments(&player);
	init_player(&player);
	init_textures(&player);
	player.img.mlx = mlx_init(player.mes.win_width, player.mes.win_height, "cub3D", 0);
	player.img.img = mlx_new_image(player.img.mlx, player.mes.win_width, player.mes.win_height);
	mlx_key_hook(player.img.mlx, key_func, &player);
	mlx_loop_hook(player.img.mlx, loop, &player);
	mlx_loop(player.img.mlx);
	return 0;
}
