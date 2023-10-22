
#include "../cub3d.h"

int	**fill_color_array(mlx_texture_t *side)
{
	int	y;
	int	x;
	int	**pixel_holder;
	int	pixel;

	pixel = 0;
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
			pixel_holder[y][x] = (side->pixels[pixel] << 24)
				| (side->pixels[pixel + 1] << 16)
				| (side->pixels[pixel + 2] << 8)
				| side->pixels[pixel + 3];
			pixel += 4;
		}
	}
	return (pixel_holder);
}
