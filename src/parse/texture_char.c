/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/17 02:07:28 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_path(char *line, int *i, int *start)
{
	int	end;

	*i = *i + 2;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (line [*i] == '\0' || line [*i] == '\n' || line [*i] == '\r')
	{
		printf("Error\nno value");
		return (0);
	}
	*start = *i;
	while (line[*i] && line[*i] != '\n' && line[*i] != '\r')
		(*i)++;
	end = *i - 1;
	while ((end >= *start) && (line[end] == ' ' || line[end] == '\t'))
		end--;
	*i = end + 1;
	if (end - *start + 1 >= 5)
	{
		end = end - 3;
		if (!(ft_strncmp(line + end, ".xpm", 4) == 0))
		{
			printf("Error\nInvalid path\n");
			return (0);
		}
	}
	else
	{
		printf("Error\nInvalid path\n");
		return (0);
	}
	return (1);
}

int	texture_char(t_config *config, char *line, int *i)
{
	int		start;
	char	**path;

	start = 0;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (ft_strncmp(line + *i, "NO", 2) == 0
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
	{
		if (config->no == NULL)
			path = &config->no;
		else
		{
			printf("Error\nmore than one value for (NO)");
			return (0);
		}
	}
	else if (ft_strncmp(line + *i, "SO", 2) == 0
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
	{
		if (config->so == NULL)
			path = &config->so;
		else
		{
			printf("Error\nmore than one value for (SO)");
			return (0);
		}
	}
	else if (ft_strncmp(line + *i, "WE", 2) == 0
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
	{
		if (config->we == NULL)
			path = &config->we;
		else
		{
			printf("Error\nmore than one value for (WE)");
			return (0);
		}
	}
	else if (ft_strncmp(line + *i, "EA", 2) == 0
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
	{
		if (config->ea == NULL)
			path = &config->ea;
		else
		{
			printf("Error\nmore than one value for (EA)");
			return (0);
		}
	}
	else
		return (0);
	if (!get_path(line, i, &start))
		return (0);
	*path = ft_substr(line, start, *i - start);
	if (!*path)
	{
		printf("Error\nInvalid malloc");
		return (0);
	}
	return (1);
}
