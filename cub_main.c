/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:03:12 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/14 17:11:40 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	north_path(t_map *map, char *str)
{
	int	i;

	i = 0;
	if (map->no)
		return(perror("Error : Double Path :/"), exit(1));
	i += 2;
	while (str[i] == ' ')
		i++;
	map->no = ft_strdup(str + i);
	if (!map->no)
		return (perror("Error : No Path Here :/"), exit(1));
}

void	south_path(t_map *map, char *str)
{
	int	i;

	i = 0;
	if (map->no)
		return(perror("Error : Double Path :/"), exit(1));
	i += 2;
	while (str[i] == ' ')
		i++;
	map->no = ft_strdup(str + i);
	if (!map->no)
		return (perror("Error : No Path Here :/"), exit(1));
}

void	west_path(t_map *map, char *str)
{
	int	i;

	i = 0;
	if (map->no)
		return(perror("Error : Double Path :/"), exit(1));
	i += 2;
	while (str[i] == ' ')
		i++;
	map->no = ft_strdup(str + i);
	if (!map->no)
		return (perror("Error : No Path Here :/"), exit(1));
}

void	east_path(t_map *map, char *str)
{
	int	i;

	i = 0;
	if (map->no)
		return(perror("Error : Double Path :/"), exit(1));
	i += 2;
	while (str[i] == ' ')
		i++;
	map->no = ft_strdup(str + i);
	if (!map->no)
		return (perror("Error : No Path Here :/"), exit(1));
}

void	creat_struct_map(t_map *map, char **av)
{
	char	*line;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return(perror("Error: File Not Found :/"), exit(EXIT_FAILURE));
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'N' && line[1] == 'O')
			north_path(map, line);
		if (line[0] == 'S' && line[1] == 'O')
			south_path(map, line);
		if (line[0] == 'W' && line[1] == 'E')
			west_path(map, line);
		if (line[0] == 'E' && line[1] == 'A')
			east_path(map, line);
		line++;
	}
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		t_map *map_intial;

		map_intial = NULL;	
		creat_struct_map(map_intial, av);
	}
	return (0);
}