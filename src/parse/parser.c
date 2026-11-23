/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/10/08 17:25:23 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_file(t_map *map, t_config *config, t_player *player)
{
	char	*line;
	int		fd;
	int		i;
	int		num_line;

	num_line = 0;
	fd = open("src/test/test.cub", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		if (line[i] == '1')
			num_line++;
		free(line);
		line = get_next_line(fd);
	}
	map->map_height = num_line;
	close(fd);
	map->map_data = malloc((num_line + 1) * sizeof(char *));
	if (!map->map_data)
		return ;
	map->map_data[map->map_height] = NULL;
	num_line = 0;
	fd = open("src/test/test.cub", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		texture_char(config, line, &i);
		texture_num(config, line, &i);
		if (line[i] == '1')
		{
			map_data(map, line, &i, num_line);
			num_line++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	find_player(map, player);
}

void	map_data(t_map *map, char *line, int *i, int num_line)
{
	int		len;

	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	map->map_width = len;
	map->map_data[num_line] = ft_substr(line, 0, len);
}

void	find_player(t_map *map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map->map_data[y])
	{
		x = 0;
		while (map->map_data[y][x])
		{
			if (map->map_data[y][x] == 'N')
			{
				player->x = x + 0.5;
				player->y = y + 0.5;
				player->x_direction = 0;
				player->y_direction = -1;
				player->angle = -PI / 2;
				return ;
			}
			else if (map->map_data[y][x] == 'S')
			{
				player->x = x + 0.5;
				player->y = y + 0.5;
				player->x_direction = 0;
				player->y_direction = 1;
				player->angle = PI / 2;
				return ;
			}
			else if (map->map_data[y][x] == 'E')
			{
				player->x = x + 0.5;
				player->y = y + 0.5;
				player->x_direction = 1;
				player->y_direction = 0;
				player->angle = 0;
				return ;
			}
			else if (map->map_data[y][x] == 'W')
			{
				player->x = x + 0.5;
				player->y = y + 0.5;
				player->x_direction = -1;
				player->y_direction = 0;
				player->angle = PI;
				return ;
			}
			x++;
		}
		y++;
	}
}
