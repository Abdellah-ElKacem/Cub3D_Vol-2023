/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:31:35 by ael-kace          #+#    #+#             */
/*   Updated: 2023/11/01 18:48:40 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


void	moving_curs(t_player *player)
{
	static int mx;
	static int my;
	static int	lastPosition;
	int			direction;

	lastPosition = mx;
	// mlx_set_cursor_mode(player->img.mlx, MLX_MOUSE_HIDDEN);
	mlx_get_mouse_pos(player->img.mlx, &mx, &my);
	if (lastPosition != mx) {
		if (mx > lastPosition)
			direction = 2;
		else 
			direction = -2;
		player->rotation_angle += direction * 2 * (M_PI / 180);
	}
	if (mx >= 2335 || mx <= -864)
		mlx_set_mouse_pos(player->img.mlx, 500, my);
	// printf("%d\n", mx);
	// return (1);
}

void	loop(void *d)
{
	t_player	*player;
	// mlx_key_data_t keydata;

	player = (t_player *)d;
	// if (keydata.key == MLX_KEY_Q)
	// {
	// 	puts("herte");
	// }
		moving_curs(player);
	draw_player(player);
	mlx_image_to_window(player->img.mlx, player->img.img, 0, 0);
}
