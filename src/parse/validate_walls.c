/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 04:15:21 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player_on_floor(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_bounds(t_map *map, int x, int y)
{
	int	len;
	int	len_up;
	int	len_down;

	if (x == 0 || x == map->map_height - 1)
		return (0);
	len_up = ft_strlen(map->map_data[x - 1]);
	len_down = ft_strlen(map->map_data[x + 1]);
	len = ft_strlen(map->map_data[x]);
	if (y == 0 || y == len - 1 || y >= len_up || y >= len_down)
		return (0);
	return (1);
}

static int	check_neighbors(t_map *map, int x, int y)
{
	return (map->map_data[x + 1][y] == ' '
			|| map->map_data[x - 1][y] == ' '
			|| map->map_data[x][y + 1] == ' '
			|| map->map_data[x][y - 1] == ' ');
}

static int	check_cell(t_map *map, int x, int y)
{
	if (!check_bounds(map, x, y))
		return (0);
	if (!check_neighbors(map, x, y))
		return (0);
	return (1);
}

int	validate_walls(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->map_height)
	{
		y = 0;
		while (map->map_data[x][y])
		{
			if (is_player_on_floor(map->map_data[x][y])
				&& !(check_cell(map, x, y)))
			{
				error_msg("Invalid map.");
				return (0);
			}
			y++;
		}
		x++;
	}
	return (1);
}
