/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 00:01:06 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 03:12:32 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map)
{
	map->map_data = NULL;
	map->map_height = 0;
	map->map_width = 0;
}

void	free_map(t_map *map)
{
	int	x;

	x = 0;
	if (!map || !map->map_data)
		return ;
	while (map->map_data[x])
	{
		free(map->map_data[x]);
		x++;
	}
	free(map->map_data);
	map->map_data = NULL;
}

char	*map_data(t_map *map, char *line, int num_line)
{
	int		len;
	char	*in_line;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
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

int	allow_char_map(char *line)
{
	int	i;

	i = 0;
	if (is_empty_line(line))
		return (0);
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '\0')
			return (1);
		if (!(line[i] == '0' || line[i] == '1'
				|| line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'W' || line[i] == 'E'
				|| line[i] == ' ' || line[i] == '\n' || line[i] == '\r'))
			return (0);
		i++;
	}
	return (1);
}
