/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:32:57 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/31 15:34:28 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	moving_curs(double x_delta, double y_delta, void *param)
{
	t_player	*player;
	int			x;

	(void)y_delta;
	player = param;
	puts("here");
	x_delta = player->rotation_angle;
	x = player->turn_direction * (player->rotation_speed / 1.5);
	player->rotation_angle += x;
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
	player.img.mlx = mlx_init(player.mes.win_width,
			player.mes.win_height, "cub3D", 0);
	player.img.img = mlx_new_image(player.img.mlx,
			player.mes.win_width, player.mes.win_height);
	mlx_key_hook(player.img.mlx, key_func, &player);
	mlx_loop_hook(player.img.mlx, loop, &player);
	mlx_scroll_hook(player.img.mlx, moving_curs, &player);
	mlx_loop(player.img.mlx);
	return (0);
}
