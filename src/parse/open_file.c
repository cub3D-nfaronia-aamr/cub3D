/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 12:02:09 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	clean_file(t_map *map, t_config *config, int fd)
{
	if (fd != -1)
		close(fd);
	free_map(map);
	free_config(config);
	return (0);
}

static int	count_lines(t_map *map, char *argv)
{
	int	fd;
	int	num_line;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		error_msg("Invalid open file");
		return (0);
	}
	num_line = count_map_line(fd);
	close(fd);
	if (num_line == 0)
		return (0);
	map->map_height = num_line;
	return (num_line);
}

static int	load_file(t_map *map, t_config *config, char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		error_msg("Invalid open file");
		return (clean_file(map, config, fd));
	}
	if (!parse_file(map, config, fd))
		return (clean_file(map, config, fd));
	close(fd);
	return (1);
}

int	open_file(t_map *map, t_config *config, t_player *player, char *argv)
{
	int	num_line;

	init_config(config);
	init_map(map);
	num_line = count_lines(map, argv);
	if (num_line == 0)
		return (0);
	if (!allocate_map(map, num_line))
	{
		error_msg("Invalid malloc.");
		return (clean_file(map, config, -1));
	}
	if (!load_file(map, config, argv))
		return (0);
	if (!not_empty_config(config))
	{
		error_msg("Missing texture or color");
		return (clean_file(map, config, -1));
	}
	if (!validate_walls(map) || !validate_player(map, player))
		return (clean_file(map, config, -1));
	return (1);
}
