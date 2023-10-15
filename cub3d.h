/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:05:18 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/15 21:38:09 by ael-kace         ###   ########.fr       */
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

typedef struct  s_map
{
	char    **map;
	int     map_x;
	int     map_y;
	char    *no;
	char    *so;
	char    *we;
	char    *ea;
	int     f;
	int     c;
}               t_map;

/* ~~~~~~~~~~~~function lib_tool~~~~~~~~~~~~ */

char	*ft_strdup_gnl(const char *s1);

#endif