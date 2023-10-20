/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:42:07 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/20 21:44:55 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_wall_start_and_end(t_map *map)
{
	int	w;

	w = 0;
	while (map->map[0][w])
	{
		while (map->map[0][w] == ' ')
			w++;
		while (map->map[0][w])
		{
			if (map->map[0][w] != '1' || map->map[1][0] == '\0' \
				|| !check_space(map->map[1]))
				(write(2, "Error1 : a wall not found:/\n", 28), exit(1));
			w++;
		}
	}
	w = 0;
	while (map->map[map->map_height - 1][w] != '\0')
	{
		while (map->map[map->map_height - 1][w] == ' ')
			w++;
		if (map->map[map->map_height - 1][w] != '1' \
			|| !check_space(map->map[map->map_height - 1]))
			(write(2, "Error2 : a wall not found:/\n", 28), exit(1));
		w++;
	}
}

void	check_wall_on_the_map(t_map *map)
{
	int	h;
	int	w;

	h = 1;
	w = 0;
	while (h <= map->map_height - 2)
	{
		while (map->map[h][w] == ' ')
			w++;
		if (map->map[h][w] != '1' \
			|| map->map[h][ft_strlen_f(map->map[h]) - 1] != '1')
			(write(2, "Error2 : a wall not found:/\n", 28), exit(1));
		h++;
		w = 0;
	}
}

void	check_any_caracter(t_map *map)
{
	int	h;
	int	w;

	h = 0;
	w = 0;
	while (h < map->map_height)
	{
		while (map->map[h][w])
		{
			if (!caractere_map(map->map[h][w]))
			{
				write(2, "Error2 : we found another caracters:/\n", 39);
				exit(1);
			}
			w++;
		}
		w = 0;
		h++;
	}
}

void	check_empty_is_arounded(t_map *map)
{
	int	h;
	int	w;

	h = 1;
	w = 0;
	while (h < map->map_height - 1)
	{
		while (map->map[h][w])
		{
			if (map->map[h][w] == '0')
			{
				if (!caractere_map_1(map->map[h][w + 1]) \
					|| !caractere_map_1(map->map[h][w - 1]) \
					|| !caractere_map_1(map->map[h - 1][w]) \
					|| !caractere_map_1(map->map[h + 1][w]))
					(write(2, "Error54 : is not arounded :/\n", 30), exit(1));
			}
			w++;
		}
		w = 0;
		h++;
	}
}

void	check_player(t_map *map)
{
	int	h;
	int	w;
	int	p;

	h = 0;
	w = 0;
	p = 0;
	while (h < map->map_height)
	{
		while (map->map[h][w])
		{
			if (map->map[h][w] == 'N' || map->map[h][w] == 'W' \
				|| map->map[h][w] == 'E' || map->map[h][w] == 'S')
				p++;
			w++;
		}
		w = 0;
		h++;
	}
	if (p != 1)
		(write(2, "Error : no player found or more :/\n", 36), exit(1));
}
