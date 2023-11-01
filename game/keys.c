/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:31:58 by ael-kace          #+#    #+#             */
/*   Updated: 2023/11/01 17:45:36 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


// int	moving_curs(t_player *player)
// {
// 	static int32_t	x_delta;
// 	static int32_t	y_delta;
// 	static int32_t	tmp;


// 	tmp = x_delta;
// // printf("%d -- %d\n", x_delta, y_delta);
// 	mlx_get_mouse_pos(player->img.mlx, &x_delta, &y_delta);
// 	mlx_set_mouse_pos(player->img.mlx, x_delta, y_delta);
// // printf("---- %d -- %d\n", x_delta, y_delta);

// 	if (x_delta == tmp ) {
// 		return (0);
// 	}
// 	else {
// 		if (x_delta < tmp) {
// 			return (-1);
// 		}
// 		else{
// 			return (1);
// 		}
// 	}
// }

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
	// if (keydata.key == MLX_KEY_Q)
	// 	return ;	
}
