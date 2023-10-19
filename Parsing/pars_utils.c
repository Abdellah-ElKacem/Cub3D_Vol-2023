/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkacem <elkacem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 23:58:02 by elkacem           #+#    #+#             */
/*   Updated: 2023/10/19 23:59:03 by elkacem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_space(char *str)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			space++;
		i++;
	}
	if (ft_strlen_f(str) == space)
		return(0);
	else
		return(1);
}
