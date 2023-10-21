#include "cub3d.h"

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
		mlx_put_pixel(player->img.img, x * player->mes.mini_map_scale,
			y * player->mes.mini_map_scale, player->color.yellow);
		x += x_increment;
		y += y_increment;
	}
}

int	texture_mapping(t_player *player, int **texture, int y, int y1, double wall_strip_height, int i)
{
	int	pixel_x;
	int	pixel_y;

	if (player->ray[i].hitvertical)
		pixel_x = fmod(player->ray[i].y, player->mes.tile_size);
	else
		pixel_x = fmod(player->ray[i].x, player->mes.tile_size);
	pixel_y = y - y1;
	pixel_y *=  (player->mes.tile_size / wall_strip_height);
	if (pixel_y >= player->mes.tile_size)
		pixel_y = player->mes.tile_size - 1;
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
			mlx_put_pixel(player->img.img, x, y, player->color.ceiling_color);
		else if (y < y1 + wall_strip_height)
			mlx_put_pixel(player->img.img, x, y, texture_mapping(player, texture, y, y1, wall_strip_height, i));
		else
			mlx_put_pixel(player->img.img, x, y, player->color.floor_color);
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
	if (x < 0 || x > player->mes.map_num_colms * 64 || y < 0 || y > player->mes.map_num_rows * 64)
		return (1);
	i = floor(y / player->mes.tile_size);
	j = floor(x / player->mes.tile_size);
	if (i >= player->map.map_height || j >= player->map.map_width)
		return (1);
	return (player->map.map[i][j] == '1'); //replaye with player->map.map_grid
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

	i = x * player->mes.tile_size * player->mes.mini_map_scale;
	j = y * player->mes.tile_size * player->mes.mini_map_scale;
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
	while (++y < player->map.map_height)
	{
		x = -1;
		while (++x < player->map.map_width)
		{
			if (player->map.map[y][x] == '1')
				draw_mini_square(player, x, y, player->color.red);
			else if (player->map.map[y][x] == '0'
				|| player->map.map[y][x] == 'W'
				|| player->map.map[y][x] == 'N'
				|| player->map.map[y][x] == 'E'
				|| player->map.map[y][x] == 'S')
				draw_mini_square(player, x, y, player->color.grey);
			else
				draw_mini_square(player, x, y, player->color.black);
		}
	}
}

//check for side collision
int	player_movement(t_player *player)
{
	int	move_step;

	player->rotation_angle += player->turn_direction * player->rotation_speed;
	move_step = player->move_speed * player->walk_direction;
	if (has_wall(player, player->x + cos(player->rotation_angle) * move_step, player->y + sin(player->rotation_angle) * move_step))
		return (0);
	player->x += cos(player->rotation_angle) * move_step;
	player->y += sin(player->rotation_angle) * move_step;
	if (player->side_direction == -1)
	{
		player->x += cos(player->rotation_angle - M_PI / 2) * player->move_speed;
		player->y += sin(player->rotation_angle - M_PI / 2) * player->move_speed;
	}
	else if (player->side_direction == 1)// adding a full circle to cos() keeps it the same (cos (n + ))
	{
		player->x += cos(player->rotation_angle + M_PI / 2) * player->move_speed;
		player->y += sin(player->rotation_angle + M_PI / 2) * player->move_speed;
	}
	return (1);
}

void	draw_player(t_player *player)
{
	int	x;
	int	y;

	if (!player_movement(player))
		return ;
	cast_all_rays(player);
	render_projected_walls(player);
	draw_mini_map(player);
	y = -10;
	while (++y < 10)
	{
		x = -10;
		while (++x < 10)
			mlx_put_pixel(player->img.img, (player->x + x) * player->mes.mini_map_scale,
				(player->y + y) * player->mes.mini_map_scale, player->color.green);
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
			if (player->map.map[x][y] == 'N' || player->map.map[x][y] == 'S' || player->map.map[x][y] == 'E' || player->map.map[x][y] == 'W')
			{
				player->x = y * player->mes.tile_size;
				player->y = x * player->mes.tile_size;
				if (player->map.map[x][y] == 'N')
					player->rotation_angle = M_PI * 1.5;
				else if (player->map.map[x][y] == 'S')
					player->rotation_angle = M_PI / 2;
				else if (player->map.map[x][y] == 'E')
					player->rotation_angle = 0;
				else if (player->map.map[x][y] == 'W')
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
	player->move_speed = 3.0;
	player->rotation_speed = 2 * (M_PI / 180);
	find_neemo(player);
}

void	init_mesurments(t_player *player)
{
	player->mes.tile_size = 64;
	player->mes.map_num_rows = player->map.map_height;
	player->mes.map_num_colms = player->map.map_width;
	player->mes.win_width = 1472;
	player->mes.win_height = 1024;
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
		player->side_direction = -1;
	else if (keydata.action == MLX_RELEASE)
		player->side_direction = 0;
}

void	key_d(t_player *player, mlx_key_data_t keydata)
{
	if (keydata.action == MLX_PRESS)
		player->side_direction = 1;
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
	int pixel;

	pixel = 0;
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

//south side is broken ? + check for leaks when path is wrong
void	init_textures(t_player *player)
{
	mlx_texture_t	*no_side;
	mlx_texture_t	*we_side;
	mlx_texture_t	*ea_side;
	mlx_texture_t	*so_side;

	no_side = mlx_load_png(player->map.no);
	ea_side = mlx_load_png(player->map.ea);
	so_side = mlx_load_png(player->map.so);
	we_side = mlx_load_png(player->map.we);
	if (!no_side || !ea_side || !so_side || !we_side)
		(write(2, "Error:\nProblem loading textures!\n", 34), exit(1));
	player->textures.no_side = fill_color_array(no_side);
	player->textures.ea_side = fill_color_array(ea_side);
	player->textures.so_side = fill_color_array(so_side);
	player->textures.we_side = fill_color_array(we_side);
	mlx_delete_texture(no_side);
	mlx_delete_texture(ea_side);
	mlx_delete_texture(so_side);
	mlx_delete_texture(we_side);
}

void	init_color(t_player *player)
{
	player->color.ceiling_color = (player->map.c.r << 24) | (player->map.c.g << 16) | (player->map.c.b << 8) | 0xFF;
	player->color.floor_color = (player->map.f.r << 24) | (player->map.f.g << 16) | (player->map.f.b << 8) | 0xFF;
	player->color.red = 255 << 24 | 0 << 16 | 0 << 8 | 0xFF;
	player->color.green = 0 << 24 | 128 << 16 | 128 << 8 | 0xFF;
	player->color.grey = 128 << 24 | 128 << 16 | 128 << 8 | 0xFF;
	player->color.yellow = 255 << 24 | 255 << 16 | 0 << 8 | 0xFF;
	player->color.black = 0 << 24 | 0 << 16 | 0 << 8 | 0xFF;
}

int	main(int ac, char **av)
{
	t_player	player;

	if (ac != 2)
		(write(2, "Error:\nWrong number of arguments!\n", 35), exit(1));
	parcing(&player, av);
	init_color(&player);
	init_mesurments(&player);
	init_player(&player);
	init_textures(&player);
	player.img.mlx = mlx_init(player.mes.win_width, player.mes.win_height, "cub3D", 0);
	player.img.img = mlx_new_image(player.img.mlx, player.mes.win_width, player.mes.win_height);
	mlx_key_hook(player.img.mlx, key_func, &player);
	mlx_loop_hook(player.img.mlx, loop, &player);
	mlx_loop(player.img.mlx);
	return (0);
}
