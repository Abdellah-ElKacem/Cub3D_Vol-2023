/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:05:18 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/17 19:45:38 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_h
# define CUB3D_h

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "g_n_l/get_next_line.h"

typedef struct  s_rgba
{
	int	r;
	int	g;
	int	b;
}               t_rgba;

typedef struct  s_map
{
	char    **map;
	int     map_height;
	int     map_weight;
	char    *no;
	char    *so;
	char    *we;
	char    *ea;
	t_rgba	f;
	t_rgba	c;
	
}               t_map;

/* ~~~~~~~~~~~~function lib_tool~~~~~~~~~~~~ */

char	*ft_strdup_gnl(const char *s1);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_atoi(const char *str);

/* ~~~~~~~~~~~~function parsing~~~~~~~~~~~~ */

char	*ft_strdup_plus(const char *s1, int len, int start, int *end);


#endif