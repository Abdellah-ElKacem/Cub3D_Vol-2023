
#include "../cub3d.h"

void	loop(void *d)
{
	t_player	*player;

	player = (t_player *)d;
	draw_player(player);
	mlx_image_to_window(player->img.mlx, player->img.img, 0, 0);
}
