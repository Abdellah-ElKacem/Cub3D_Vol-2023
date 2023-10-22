
#include "../cub3d.h"

int	has_wall(t_player *player, double x, double y)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (x < 0 || x > player->mes.map_num_colms * 64 || y < 0
		|| y > player->mes.map_num_rows * 64)
		return (1);
	i = floor(y / player->mes.tile_size);
	j = floor(x / player->mes.tile_size);
	if (i >= player->map.map_height || j >= player->map.map_width)
		return (1);
	return (player->map.map[i][j] == '1');
}

//check for side collision
int	player_movement(t_player *player)
{
	int	move_step;

	player->rotation_angle += player->turn_direction * player->rotation_speed;
	move_step = player->move_speed * player->walk_direction;
	if (has_wall(player, player->x + cos(player->rotation_angle) * move_step,
			player->y + sin(player->rotation_angle) * move_step))
		return (0);
	player->x += cos(player->rotation_angle) * move_step;
	player->y += sin(player->rotation_angle) * move_step;
	if (player->side_direction == -1)
	{
		player->x += cos(player->rotation_angle - M_PI / 2)
			* player->move_speed;
		player->y += sin(player->rotation_angle - M_PI / 2)
			* player->move_speed;
	}
	else if (player->side_direction == 1)
	{
		player->x += cos(player->rotation_angle + M_PI / 2)
			* player->move_speed;
		player->y += sin(player->rotation_angle + M_PI / 2)
			* player->move_speed;
	}
	return (1);
}
