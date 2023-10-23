/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:32:39 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/23 15:00:22 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	texture_mapping(t_player *player, int **texture, int y, int i)
{
	int	pixel_x;
	int	pixel_y;
	int	y1;

	y1 = (player->mes.win_height / 2) - (player->mes.wall_strip_height / 2);
	if (player->ray[i].hitvertical)
		pixel_x = fmod(player->ray[i].y, player->mes.tile_size);
	else
		pixel_x = fmod(player->ray[i].x, player->mes.tile_size);
	pixel_y = y - y1;
	pixel_y *= (player->mes.tile_size / player->mes.wall_strip_height);
	if (pixel_y >= player->mes.tile_size)
		pixel_y = player->mes.tile_size - 1;
	return (texture[pixel_y][pixel_x]);
}

void	render_projected_walls(t_player *player)
{
	double	correct_distance;
	double	distance_projection_plane;
	int		i;
	int		**texture;

	distance_projection_plane = (player->mes.win_width / 2)
		/ tan(player->mes.fov_angle / 2);
	i = -1;
	while (++i < player->mes.num_rays)
	{
		correct_distance = player->ray[i].ray_distance
			* cos(player->rotation_angle - player->ray[i].ray_angle);
		player->mes.wall_strip_height = (player->mes.tile_size
				/ correct_distance)
			* (distance_projection_plane);
		if (player->ray[i].hitvertical && player->ray[i].right_ray)
			texture = player->textures.ea_side;
		else if (player->ray[i].hitvertical && player->ray[i].left_ray)
			texture = player->textures.we_side;
		else if (!player->ray[i].hitvertical && player->ray[i].up_ray)
			texture = player->textures.no_side;
		else if (!player->ray[i].hitvertical && player->ray[i].down_ray)
			texture = player->textures.so_side;
		draw_rectangles(player, i, texture);
	}
}
