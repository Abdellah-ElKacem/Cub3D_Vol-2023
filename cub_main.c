/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:03:12 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/21 10:52:29 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map, char **av)
{
	map->map = NULL;
	map->map_height = 0;
	map->map_weight = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f.r = -1;
	map->c.r = -1;
	if (ft_strcmp(av[1] + ft_strlen_f(av[1]) - 4, ".cub"))
		(write(2, "Error : Bad Extension :/\n", 26), exit(1));
}

void	parse_map(t_map *map)
{
	check_wall_start_and_end(map);
	check_wall_on_the_map(map);
	check_player(map);
	check_any_caracter(map);
	check_empty_is_arounded(map);
	check_player_has_a_empty(map);
}

int	main(int ac, char **av)
{
	t_map	*map;

	if (ac == 2)
	{
		map = malloc(sizeof(t_map));
		if (!map)
			return (write(2, "Error Malloc !", 16));
		init_map(map, av);
		creat_struct_map(map, av);
		check_path_and_color(map);
		if (!map->map)
			(write(2, "Error : map not found:/\n", 25), exit(1));
		parse_map(map);
		printf("OK :)\n");
	}
	else
		(write(2, "Error : more that arguments :/", 31), exit(1));
	return (0);
}
