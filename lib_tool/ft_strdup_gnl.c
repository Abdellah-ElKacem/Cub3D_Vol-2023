/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_gnl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:17:27 by ael-kace          #+#    #+#             */
/*   Updated: 2023/10/15 21:37:59 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strdup_gnl(const char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
		if (s1[i] == '\n')
			return (str[i] = '\0', str);
	}
	str[i] = '\0';
	return (str);
}
