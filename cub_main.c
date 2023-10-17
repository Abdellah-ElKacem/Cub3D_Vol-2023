/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:03:12 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/17 21:53:15 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	north_path(t_map *map, char *str, int *i)
{
	if (map->no)
		return (write(2, "Error : Double Path :/\n", 24), exit(1));
	while (str[*i] == ' ')
		(*i)++;
	map->no = ft_strdup_gnl(str + *i);
	if (map->no[0] == '\0')
		return (write(2, "Error : No Path Here :/\n", 25), exit(1));
}

void	south_path(t_map *map, char *str, int *i)
{
	if (map->so)
		return (write(2, "Error : Double Path :/\n", 24), exit(1));
	while (str[*i] == ' ')
		(*i)++;
	map->so = ft_strdup_gnl(str + *i);
	if (map->so[0] == '\0')
		return (write(2, "Error : No Path Here :/\n", 25), exit(1));
}

void	west_path(t_map *map, char *str, int *i)
{
	if (map->we)
		return (write(2, "Error : Double Path :/\n", 24), exit(1));
	while (str[*i] == ' ')
		(*i)++;
	map->we = ft_strdup_gnl(str + *i);
	if (map->we[0] == '\0')
		return (write(2, "Error : No Path Here :/\n", 25), exit(1));
}

void	east_path(t_map *map, char *str, int *i)
{
	if (map->ea)
		return (write(2, "Error : Double Path :/\n", 24), exit(1));
	while (str[*i] == ' ')
		(*i)++;
	map->ea = ft_strdup_gnl(str + *i);
	if (map->ea[0] == '\0')
		return (write(2, "Error : No Path Here :/\n", 25), exit(1));
}

void	check_path(t_map *map, char *line, int *i)
{
	if (line[*i] == 'N' && line[*i + 1] == 'O')
	{
		*i += 2;
		north_path(map, line, i);
	}
	else if (line[*i] == 'S' && line[*i + 1] == 'O')
	{
		*i += 2;
		south_path(map, line, i);
	}
	else if (line[*i] == 'W' && line[*i + 1] == 'E')
	{
		*i += 2;
		west_path(map, line, i);
	}
	else if (line[*i] == 'E' && line[*i + 1] == 'A')
	{
		*i += 2;
		east_path(map, line, i);
	}
	else
		(write(2, "ERROR !", 8), exit(1));
}

void	put_on_the_right_place_f(t_map *map, char *str, int idx)
{
	if (!str)
		return (write(2, "Error : of color path:/\n", 25), exit(1));
	if (idx == 1)
	{
		if (map->f.r != -1)
			return (write(2, "Error : of color path:/\n", 25), exit(1));
		map->f.r = ft_atoi(str);
		if (map->f.r < 0 || map->f.r > 255)
			return (write(2, "Error : of color path:/\n", 25), exit(1));
	}
	else if (idx == 2)
	{
		map->f.g = ft_atoi(str);
		if (map->f.g < 0 || map->f.g > 255)
			return (write(2, "Error : of color path:/\n", 25), exit(1));
	}
	else if (idx == 3)
	{
		map->f.b = ft_atoi(str);
		if (map->f.b < 0 || map->f.b > 255)
			return (write(2, "Error : of color path:/\n", 25), exit(1));
	}
	else
		return (write(2, "Error : of color path:/\n", 25), exit(1));
}

void	put_on_the_right_place_c(t_map *map, char *str, int idx)
{
	if (!str)
		return (write(2, "Error : of color path:/\n", 25), exit(1));
	if (idx == 1)
	{
		if (map->c.r != -1)
			return (write(2, "Error : of color path:/\n", 25), exit(1));
		map->c.r = ft_atoi(str);
		if (map->c.r < 0 || map->c.r > 255)
			return (write(2, "Error : of color path:/\n", 25), exit(1));
	}
	else if (idx == 2)
	{
		map->c.g = ft_atoi(str);
		if (map->c.g < 0 || map->c.g > 255)
			return (write(2, "Error : of color path:/\n", 25), exit(1));
	}
	else if (idx == 3)
	{
		map->c.b = ft_atoi(str);
		if (map->c.b < 0 || map->c.b > 255)
			return (write(2, "Error : of color path:/\n", 25), exit(1));
	}
	else
		return (write(2, "Error : of color path:/\n", 25), exit(1));
}

void	error_digit(char *line, int *i, int *len, int idx)
{
	if (!ft_isdigit(line[*i]))
		return (write(2, "Error1 : of color path:/\n", 25), exit(1));
	if (idx == 1)
	{
		(*len)++;
		(*i)++;
	}
}

void	check_v(int v)
{
	if (v != 2)
		return (write(2, "Error : of color path:/\n", 25), exit(1));
}

void	put_colors_f(t_map *map, char *line, int *i)
{
	char	*str;
	int		v;
	int		idx;
	int		len;
	int		start;

	v = 0;
	idx = 1;
	len = 0;
	while (line[*i] == ' ')
		(*i)++;
	error_digit(line, i, &len, 0);
	while (line[*i])
	{
		start = *i;
		while (line[*i] != ',' && line[*i] != '\n' && line[*i])
			error_digit(line, i, &len, 1);
		str = ft_strdup_plus(line, len, start, i);
		(put_on_the_right_place_f(map, str, idx), idx++);
		len = 0;
		if (line[*i] == ',')
			v++;
		(*i)++;
	}
	check_v(v);
}

void	put_colors_c(t_map *map, char *line, int *i)
{
	char	*str;
	int		v;
	int		idx;
	int		len;
	int		start;

	v = 0;
	idx = 1;
	len = 0;
	while (line[*i] == ' ')
		(*i)++;
	error_digit(line, i, &len, 0);
	while (line[*i])
	{
		start = *i;
		while (line[*i] != ',' && line[*i] != '\n' && line[*i])
			error_digit(line, i, &len, 1);
		str = ft_strdup_plus(line, len, start, i);
		(put_on_the_right_place_c(map, str, idx), idx++);
		len = 0;
		if (line[*i] == ',')
			v++;
		(*i)++;
	}
	check_v(v);
}

void	check_colors(char *line, t_map *map, int *i)
{
	if (line[*i] == 'F')
	{
		*i += 1;
		put_colors_f(map, line, i);
	}
	if (line[*i] == 'C')
	{
		*i += 1;
		put_colors_c(map, line, i);
	}
}

void	creat_map1(t_map *map, char *line, int fd, int len)
{
	map->map = (char **)malloc(sizeof(char *) * (len + 1));
	if (!map->map)
		return ;
	map->map_weight = ft_strlen(line) - 1;
	while (line)
	{
		map->map[map->map_height] = ft_strdup_gnl(line);
		map->map_height++;
		(free(line), line = get_next_line(fd));
	}
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

void	init_map(t_map *map)
{
	map->map = NULL;
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
		t_map	*map_intial;

		map_intial = malloc(sizeof(t_map));
		if (!map_intial)
			return (write(2, "Error Malloc !", 16));
		init_map(map_intial);
		creat_struct_map(map_intial, av);
		check_path_and_color(map_intial);
		if (!map_intial->map)
			(write(2, "Error : map not found:/\n", 25), exit(1));
		puts(map_intial->no);
		puts(map_intial->so);
		puts(map_intial->we);
		puts(map_intial->ea);
		printf("r = %d\n", map_intial->f.r);
		printf("g = %d\n", map_intial->f.g);
		printf("b = %d\n", map_intial->f.b);
		printf("r_c = %d\n", map_intial->c.r);
		printf("g_c = %d\n", map_intial->c.g);
		printf("b_c = %d\n", map_intial->c.b);
		printf("OK :)\n");
	}
	else
		(write(2, "Error : more that arguments :/", 31), exit(1));
	return (0);
}
