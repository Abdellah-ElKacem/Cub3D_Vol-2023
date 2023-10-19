/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkacem <elkacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:03:12 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/20 00:28:55 by elkacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_wall_start_and_end(t_map *map)
{
	int w;
	
	w = 0;
	while (map->map[0][w])
	{
		if (map->map[1][0] == '\0' || !check_space(map->map[1]))
			(write(2, "Error : a wall not found:/\n", 28), exit(1));
		while (map->map[0][w] == ' ')
			w++;
		while (map->map[0][w])
		{
			if (map->map[0][w] != '1')
				(write(2, "Error1 : a wall not found:/\n", 28), exit(1));
			w++;
		}
	}
	w = 0;
	while (map->map[map->map_height - 1][w] != '\0')
	{
		while (map->map[map->map_height - 1][w] == ' ')
			w++;
		if (map->map[map->map_height - 1][w] != '1' || !check_space(map->map[map->map_height - 1]))
			(write(2, "Error2 : a wall not found:/\n", 28), exit(1));
		w++;
	}
}

void	check_wall_on_the_map(t_map *map)
{
	int h;
	int w;

	h = 1;
	w = 0;
	while (h <= map->map_height - 2)
	{
		while (map->map[h][w] == ' ')
			w++;
		if (map->map[h][w] != '1' && map->map[h][ft_strlen_f(map->map[h]) - 1] != '1')
			(write(2, "Error2 : a wall not found:/\n", 28), exit(1));
		h++;
		w = 0;
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
		while(map->map[h][w])
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
			(write(2, "Error : no player found:/\n", 27), exit(1));
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->map_height = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f.r = -1;
	map->c.r = -1;
}

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		t_map	*map;

		map = malloc(sizeof(t_map));
		if (!map)
			return (write(2, "Error Malloc !", 16));
		init_map(map);
		creat_struct_map(map, av);
		check_path_and_color(map);
		if (!map->map)
			(write(2, "Error : map not found:/\n", 25), exit(1));
		// check_wall_start_and_end(map);
		check_wall_on_the_map(map);
		check_player(map);
		int jj = 0;
		while (jj <= map->map_height)
		{
			printf("[%s]\n", map->map[jj]);
			jj++;
		}
			// printf("[%s]\n", map->map[0]);
		printf("OK :)\n");
	}
	else
		(write(2, "Error : more that arguments :/", 31), exit(1));
	return (0);
}
