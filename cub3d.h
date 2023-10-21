/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:05:18 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/21 10:51:58 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "g_n_l/get_next_line.h"

typedef struct s_rgba
{
	int	r;
	int	g;
	int	b;
}				t_rgba;

typedef struct s_map
{
	char	**map;
	int		map_height;
	int		map_weight;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_rgba	f;
	t_rgba	c;
}				t_map;

/* ~~~~~~~~~~~~function lib_tool~~~~~~~~~~~~ */

char	*ft_strdup_gnl(const char *s1);
int		ft_strlen_f(char *s);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_atoi(const char *str);
int		ft_strcmp(char *str1, char *str2);

/* ~~~~~~~~~~~~function parsing~~~~~~~~~~~~ */

char	*ft_strdup_plus(const char *s1, int len, int start, int *end);
void	creat_map1(t_map *map, char *line, int fd, int len);
void	check_path_and_color(t_map *map);
void	creat_map(t_map *map, char *line, int fd, char **av);
void	creat_struct_map(t_map *map, char **av);
void	north_path(t_map *map, char *str, int *i);
void	south_path(t_map *map, char *str, int *i);
void	west_path(t_map *map, char *str, int *i);
void	east_path(t_map *map, char *str, int *i);
void	check_path(t_map *map, char *line, int *i);
void	put_colors_c(t_map *map, char *line, int *i);
void	check_colors(char *line, t_map *map, int *i);
void	put_on_the_right_place_f(t_map *map, char *str, int idx);
void	put_on_the_right_place_c(t_map *map, char *str, int idx);
void	error_digit(char *line, int *i, int *len, int idx);
void	check_v(int v);
void	put_colors_f(t_map *map, char *line, int *i);
int		check_space(char *str);
void	check_wall_start_and_end(t_map *map);
void	check_wall_on_the_map(t_map *map);
void	check_any_caracter(t_map *map);
void	check_empty_is_arounded(t_map *map);
void	check_player(t_map *map);
void	check_player_has_a_empty(t_map *map);
int		caractere_map(int c);
int		caractere_map_1(int c);
int		caractere_map_2(int c);

#endif