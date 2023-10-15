/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:03:12 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/15 21:47:18 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	north_path(t_map *map, char *str, int *i)
{
	if (map->no)
		return (write(2,"Error : Double Path :/", 23), exit(1));
	while (str[*i] == ' ')
		(*i)++;
	map->no = ft_strdup_gnl(str + *i);
	if (!map->no|| map->no[0] == '\0')
		return (write(2,"Error : No Path Here :/", 24), exit(1));
}

void	south_path(t_map *map, char *str, int *i)
{
	if (map->so)
		return (write(2,"Error : Double Path :/", 23), exit(1));
	while (str[*i] == ' ')
		(*i)++;
	map->so = ft_strdup_gnl(str + *i);
	if (!map->so|| map->so[0] == '\0')
		return (write(2,"Error : No Path Here :/", 24), exit(1));
}

void	west_path(t_map *map, char *str, int *i)
{
	if (map->we)
		return (write(2,"Error : Double Path :/", 23), exit(1));
	while (str[*i] == ' ')
		(*i)++;
	map->we = ft_strdup_gnl(str + *i);
	if (!map->we|| map->we[0] == '\0')
		return (write(2,"Error : No Path Here :/", 24), exit(1));
}

void	east_path(t_map *map, char *str, int *i)
{
	if (map->ea)
		return (write(2,"Error : Double Path :/", 23), exit(1));
	while (str[*i] == ' ')
		(*i)++;
	map->ea = ft_strdup_gnl(str + *i);
	if (!map->ea || map->ea[0] == '\0')
		return (write(2,"Error : No Path Here :/", 24), exit(1));
}

void	check_path(t_map *map, char *line, int *i)
{
	if (line[*i] == 'N' && line[*i + 1] == 'O')
		(*i += 2, north_path(map, line, i));
	else if (line[*i] == 'S' && line[*i + 1] == 'O')
		(*i += 2, south_path(map, line, i));
	else if (line[*i] == 'W' && line[*i + 1] == 'E')
		(*i += 2, west_path(map, line, i));
	else if (line[*i] == 'E' && line[*i + 1] == 'A')
		(*i += 2, east_path(map, line, i));
	else
		(write(2, "ERROR !", 8), exit(1));
}

void	creat_struct_map(t_map *map, char **av)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return(perror("Error Found"), exit(1));
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
			check_path(map, line, &i);
		free(line);
		line = get_next_line(fd);
		i = 0;
	}
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->map_x = 0;
	map->map_y = 0;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f = 0;
	map->c = 0;
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		t_map *map_intial;

		map_intial = malloc(sizeof(t_map));
		if (!map_intial)
			return (write(2,"Error Malloc !", 16));
		init_map(map_intial);
		creat_struct_map(map_intial, av);
		puts(map_intial->no);
		puts(map_intial->so);
		puts(map_intial->we);
		puts(map_intial->ea);
		printf("OK :)\n");
	}
	return (0);
}
