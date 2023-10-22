/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:31:35 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/22 17:31:37 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	loop(void *d)
{
	t_player	*player;

	player = (t_player *)d;
	draw_player(player);
	mlx_image_to_window(player->img.mlx, player->img.img, 0, 0);
}
