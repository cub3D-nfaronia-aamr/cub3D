/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 11:17:17 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_line(char *line, int *in_map, int *end_map, int *num_line)
{
	int	i;

	i = 0;
	skip_spaces(line, &i);
	if (is_empty_line(line + i) && *in_map == 0 && *end_map == 0)
		return (1);
	if (is_direction_line(line + i) && *in_map == 0 && *end_map == 0)
		return (1);
	if (is_color_line(line + i) && *in_map == 0 && *end_map == 0)
		return (1);
	if (allow_char_map(line + i) && *end_map == 0)
	{
		*in_map = 1;
		(*num_line)++;
		return (1);
	}
	if (is_empty_line(line) && *in_map == 1)
	{
		*end_map = 1;
		return (1);
	}
	return (0);
}

int	count_map_line(int fd)
{
	char	*line;
	int		num_line;
	int		in_map;
	int		end_map;

	num_line = 0;
	in_map = 0;
	end_map = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!check_line(line, &in_map, &end_map, &num_line))
		{
			error_msg("Invalid line");
			return (fail_line(line));
		}
		free(line);
		line = get_next_line(fd);
	}
	if (num_line == 0)
	{
		error_msg("Invalid map");
		return (0);
	}
	return (num_line);
}

static int	parse_line(t_map *map, t_config *config, char *line, int *num_line)
{
	int	i;

	i = 0;
	skip_spaces(line, &i);
	if (is_empty_line(line + i) && *num_line == 0)
		return (1);
	if (is_direction_line(line + i) && *num_line == 0)
		return (texture_char(config, line, &i));
	if (is_color_line(line + i) && *num_line == 0)
		return (texture_num(config, line, &i));
	if (!allow_char_map(line + i) || *num_line >= map->map_height)
	{
		error_msg("Invalid line");
		return (0);
	}
	if (!map_data(map, line, *num_line))
	{
		error_msg("malloc failed");
		return (0);
	}
	(*num_line)++;
	return (1);
}

static int	read_lines(t_map *map, t_config *config, int fd, int *num_line)
{
	char	*line;
	int		end_map;

	end_map = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (end_map == 1 && !is_empty_line(line))
		{
			error_msg("Invalid line after map.");
			return (fail_line(line));
		}
		if (end_map == 0 && *num_line > 0 && is_empty_line(line))
			end_map = 1;
		else if (end_map == 0 && !parse_line(map, config, line, num_line))
			return (fail_line(line));
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	parse_file(t_map *map, t_config *config, int fd)
{
	int	num_line;

	num_line = 0;
	if (!read_lines(map, config, fd, &num_line))
		return (0);
	if (num_line != map->map_height)
	{
		error_msg("Invalid map");
		return (0);
	}
	return (1);
}
