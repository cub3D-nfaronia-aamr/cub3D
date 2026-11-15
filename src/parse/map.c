/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 00:01:06 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/15 08:11:02 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *map)
{
	int	x;

	x = 0;
	if (map->map_data)
	{
		while (map->map_data[x])
		{
			free(map->map_data[x]);
			x++;
		}
	}
	free(map->map_data);
	map->map_data = NULL;
}

char	*map_data(t_map *map, char *line, int num_line)
{
	int		len;
	char	*in_line;

	len = ft_strlen(line);
	if (!(len == 0) && line[len - 1] == '\n')
		len--;
	if (len > map->map_width)
		map->map_width = len;
	in_line = ft_substr(line, 0, len);
	if (!in_line)
		return (NULL);
	map->map_data[num_line] = in_line;
	return (map->map_data[num_line]);
}

int	allocate_map(t_map *map, int num_line)
{
	int	i;

	i = 0;
	map->map_data = malloc((num_line + 1) * sizeof(char *));
	if (!map->map_data)
		return (0);
	while (i <= num_line)
	{
		map->map_data[i] = NULL;
		i++;
	}
	return (1);
}
