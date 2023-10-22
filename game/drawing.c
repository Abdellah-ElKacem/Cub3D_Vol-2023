/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:31:40 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/22 17:31:42 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_win(t_player *player)
{
	if (player->img.img)
		mlx_delete_image(player->img.mlx, player->img.img);
	player->img.img = mlx_new_image(player->img.mlx,
			player->mes.win_width, player->mes.win_height);
}

void	draw_rectangles(t_player *player, int x, int **texture)
{
	int	y;
	int	y1;

	y1 = (player->mes.win_height / 2) - (player->mes.wall_strip_height / 2);
	y = -1;
	while (++y < player->mes.win_height)
	{
		if (y < y1)
			mlx_put_pixel(player->img.img, x, y, player->color.ceiling_color);
		else if (y < y1 + player->mes.wall_strip_height)
			mlx_put_pixel(player->img.img, x, y,
				texture_mapping(player, texture, y, x));
		else
			mlx_put_pixel(player->img.img, x, y, player->color.floor_color);
	}
}

void	draw_player(t_player *player)
{
	if (!player_movement(player))
		return ;
	cast_all_rays(player);
	render_projected_walls(player);
}
