/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 22:50:08 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/11 23:58:04 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_players(t_map *map)
{
	int	x;
	int	y;
	int	num_of_player;

	y = 0;
	num_of_player = 0;
	while (map->map_data[y])
	{
		x = 0;
		while (map->map_data[y][x])
		{
			if (map->map_data[y][x] == 'N' || map->map_data[y][x] == 'S'
			|| map->map_data[y][x] == 'E' || map->map_data[y][x] == 'W')
				num_of_player++;
			x++;
		}
		y++;
	}
	if (num_of_player != 1)
		return (0);
	else
		return (1);
}

static void	init_player(t_player *player, int x, int y)
{
	player->x = x + 0.5;
	player->y = y + 0.5;
	player->x_direction = 0;
	player->y_direction = 0;
	player->angle = 0;
}

static void	set_player_direction(t_map *map, t_player *player, int x, int y)
{
	init_player(player, x, y);
	if (map->map_data[y][x] == 'N')
	{
		player->y_direction = -1;
		player->angle = -PI / 2;
		return ;
	}
	else if (map->map_data[y][x] == 'S')
	{
		player->y_direction = 1;
		player->angle = PI / 2;
		return ;
	}
	else if (map->map_data[y][x] == 'E')
	{
		player->x_direction = 1;
		return ;
	}
	else if (map->map_data[y][x] == 'W')
	{
		player->x_direction = -1;
		player->angle = PI;
		return ;
	}
}

void	locate_player(t_map *map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map->map_data[y])
	{
		x = 0;
		while (map->map_data[y][x])
		{
			if (map->map_data[y][x] == 'N' || map->map_data[y][x] == 'S'
			|| map->map_data[y][x] == 'E' || map->map_data[y][x] == 'W')
			{
				set_player_direction(map, player, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
}
