/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:45:14 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/18 23:53:32 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	creat_map1(t_map *map, char *line, int fd, int len)
{
	// printf("%d\n", len);
	map->map = (char **)malloc(sizeof(char *) * len + 1);
	if (!map->map)
		return ;
	map->map_weight = ft_strlen_f(line) - 1;
	while (line)
	{
	// printf("%d\n", map->map_height);
		map->map[map->map_height] = ft_strdup_gnl(line);
		map->map_height++;
		(free(line), line = get_next_line(fd));
		// if (map->map_weight < (ft_strlen_f(line) - 1))
		// 	map->map_weight = ft_strlen_f(line) - 1;
	}
	// printf("%d\n", map->map_height);
		map->map[map->map_height] = NULL;
}

void	check_path_and_color(t_map *map)
{
	if (!map->no || !map->so \
		|| !map->we || !map->ea)
		(write(2, "Error : No Path Here :/\n", 25), exit(1));
	if (map->f.r == -1 || map->c.r == -1)
		(write(2, "Error : of color path:/\n", 25), exit(1));
}

void	creat_map(t_map *map, char *line, int fd, char **av)
{
	int	len;
	int	len1;

	check_path_and_color(map);
	len = 0;
	while (line)
	{
		len++;
		(free(line), line = get_next_line(fd));
	}
	close(fd);
	fd = open(av[1], O_RDONLY);
	line = get_next_line(fd);
	len1 = 0;
	while (line)
	{
		while (line[len1] == ' ')
			len1++;
		if (ft_isprint(line[len1]))
			return (creat_map1(map, line, fd, len));
		free(line);
		line = get_next_line(fd);
		len1 = 0;
	}
}

void	creat_struct_map(t_map *map, char **av)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (perror("Error Found"), exit(1));
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == 'N' || line[i] == 'S' \
			|| line[i] == 'W' || line[i] == 'E')
			check_path(map, line, &i);
		else if (line[i] == 'F' || line[i] == 'C')
			check_colors(line, map, &i);
		else if (ft_isprint(line[i]))
			return (creat_map(map, line, fd, av));
		free(line);
		line = get_next_line(fd);
		i = 0;
	}
}
