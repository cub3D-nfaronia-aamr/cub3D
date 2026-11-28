/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 12:04:12 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_path(char *line, int start, int end)
{
	if (end - start + 1 < 5)
	{
		error_msg("Invalid path");
		return (0);
	}
	end -= 3;
	if (ft_strncmp(line + end, ".xpm", 4) != 0)
	{
		error_msg("Invalid path");
		return (0);
	}
	return (1);
}

static int	get_path(char *line, int *i, int *start)
{
	int	end;
	int	correct;

	*i = *i + 2;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line[*i] == '\0' || line[*i] == '\n' || line[*i] == '\r')
	{
		error_msg("no value");
		return (0);
	}
	*start = *i;
	while (line[*i] && line[*i] != '\n' && line[*i] != '\r')
		(*i)++;
	end = *i - 1;
	while ((end >= *start) && (line[end] == ' ' || line[end] == '\t'))
		end--;
	*i = end + 1;
	correct = check_path(line, *start, end);
	return (correct);
}

static char	**get_texture(t_config *config, char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (ft_strncmp(line + *i, "NO", 2) == 0
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
		return (&config->no);
	if (ft_strncmp(line + *i, "SO", 2) == 0
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
		return (&config->so);
	if (ft_strncmp(line + *i, "WE", 2) == 0
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
		return (&config->we);
	if (ft_strncmp(line + *i, "EA", 2) == 0
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
		return (&config->ea);
	return (NULL);
}

static int	set_texture_path(char **path, char *line, int *i)
{
	int	start;

	start = 0;
	if (!get_path(line, i, &start))
		return (0);
	*path = ft_substr(line, start, *i - start);
	if (!*path)
	{
		error_msg("malloc failed");
		return (0);
	}
	if (!correct_path(*path))
	{
		free(*path);
		*path = NULL;
		return (0);
	}
	return (1);
}

int	texture(t_config *config, char *line, int *i)
{
	int		correct;
	char	**path;

	path = get_texture(config, line, i);
	if (!path)
	{
		error_msg("Invalid texture");
		return (0);
	}
	if (*path)
	{
		error_msg("Duplicate texture");
		return (0);
	}
	correct = set_texture_path(path, line, i);
	return (correct);
}
