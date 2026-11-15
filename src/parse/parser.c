/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/15 12:49:13 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_map_line(int fd)
{
	char	*line;
	int		i;
	int		num_line;
	int		in_map;

	num_line = 0;
	in_map = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (is_empty_line(line) && in_map == 0)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else if ((ft_strncmp(line + i, "NO", 2) == 0
				|| ft_strncmp(line + i, "SO", 2) == 0
				|| ft_strncmp(line + i, "WE", 2) == 0
				|| ft_strncmp(line + i, "EA", 2) == 0)
			&& (line[i + 2] == ' ' || line[i + 2] == '\t') && in_map == 0)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else if ((line[i] == 'F' || line[i] == 'C')
			&& (line[i + 1] == ' ' || line[i + 1] == '\t') && in_map == 0)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else if (allow_char_map(line))
		{
			in_map = 1;
			num_line++;
		}
		else
		{
			printf("Error\nInvalid line");
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (num_line == 0)
	{
		printf("Error\nInvalid map");
		return (0);
	}
	return (num_line);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
			return (0);
		i++;
	}
	return (1);
}

int	allow_char_map(char *line)
{
	int	i;

	i = 0;
	if (is_empty_line(line))
		return (0);
	while (line[i])
	{
		while (line[i] == ' ' || line[i] == '\t' )
			i++;
		if (line[i] == '\0')
			return (1);
		if (!(line[i] == '0' || line[i] == '1'
				|| line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'W' || line[i] == 'E'
				|| line[i] == ' ' || line[i] == '\t'
				|| line[i] == '\n'))
			return (0);
		i++;
	}
	return (1);
}

void	init_config(t_config *config)
{
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
	config->floor.r = -1;
	config->floor.g = -1;
	config->floor.b = -1;
	config->ceiling.r = -1;
	config->ceiling.g = -1;
	config->ceiling.b = -1;
}

void	init_map(t_map *map)
{
	map->map_data = NULL;
	map->map_height = 0;
	map->map_width = 0;
}

int	parse_file(t_map *map, t_config *config, int fd)
{
	char	*line;
	int		i;
	int		num_line;
	char	*map_line;
	int		in_map;

	num_line = 0;
	in_map = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (is_empty_line(line) && in_map == 0)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else if ((ft_strncmp(line + i, "NO", 2) == 0
				|| ft_strncmp(line + i, "SO", 2) == 0
				|| ft_strncmp(line + i, "WE", 2) == 0
				|| ft_strncmp(line + i, "EA", 2) == 0) && in_map == 0)
		{
			if (!texture_char(config, line, &i))
			{
				printf("Error\nInvalid texture");
				free(line);
				return (0);
			}
		}
		else if ((line[i] == 'F' || line[i] == 'C') && in_map == 0)
		{
			if (!texture_num(config, line, &i))
			{
				printf("Error\nInvalid texture");
				free(line);
				return (0);
			}
		}
		else if (allow_char_map(line))
		{
			in_map = 1;
			if (num_line < map->map_height)
			{
				map_line = map_data(map, line, num_line);
				if (!map_line)
				{
					printf("Error\nInvalid map");
					free(line);
					return (0);
				}
				num_line++;
			}
			else
			{
				printf("Error\nInvalid line");
				free(line);
				return (0);
			}
		}
		else
		{
			printf("Error\nInvalid line");
			free(line);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (num_line != map->map_height)
	{
		printf("Error\nInvalid map");
		return (0);
	}
	return (1);
}

int	validate_player(t_map *map, t_player *player)
{
	if (count_players(map))
		locate_player(map, player);
	else
	{
		printf("Error\nInvalid number of players.");
		return (0);
	}
	return (1);
}

int	open_file(t_map *map, t_config *config, t_player *player, char *argv)
{
	int		fd;
	int		num_line;

	init_config(config);
	init_map(map);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	num_line = count_map_line(fd);
	if (num_line == 0)
	{
		printf("Error\nInvalid map");
		close(fd);
		return (0);
	}
	map->map_height = num_line;
	close(fd);
	if (!allocate_map(map, num_line))
	{
		printf("Error\nInvalid malloc");
		return (0);
	}
	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		free_map(map);
		return (0);
	}
	if (!parse_file(map, config, fd))
	{
		close(fd);
		free_map(map);
		return (0);
	}
	close(fd);
	if (validate_player(map, player))
		return (1);
	else
	{
		free_map(map);
		return (0);
	}
}
