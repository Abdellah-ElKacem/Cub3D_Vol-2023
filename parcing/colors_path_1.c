/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_path_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:51:40 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/18 10:51:56 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
