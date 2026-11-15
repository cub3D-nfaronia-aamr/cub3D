/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/15 15:13:33 by nfaronia         ###   ########.fr       */
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
	while ((end >= start) && (line[end] == ' ' || line[end] == '\t'))
		end--;
	*i = end + 1;
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

static void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

static void	rgb_data(t_config *config, char **numbers, char type)
{
	if (type == 'F')
	{
		config->floor.r = ft_atoi(numbers[0]);
		config->floor.g = ft_atoi(numbers[1]);
		config->floor.b = ft_atoi(numbers[2]);
	}
	else
	{
		config->ceiling.r = ft_atoi(numbers[0]);
		config->ceiling.g = ft_atoi(numbers[1]);
		config->ceiling.b = ft_atoi(numbers[2]);
	}
}

int	texture_num(t_config *config, char *line, int *i)
{
	int		start;
	char	*num;
	char	**numbers;
	char	type;

	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	type = line[*i];
	if ((type != 'F' && type != 'C')
		|| (line[*i + 1] != ' ' && line[*i + 1] != '\t'))
		return (0);
	(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	start = *i;
	while (line[*i] && line[*i] != '\n')
		(*i)++;
	num = ft_substr(line, start, *i - start);
	if (!num)
		return (0);
	numbers = ft_split(num, ',');
	free(num);
	if (!numbers)
		return (0);
	rgb_data(config, numbers, type);
	free_split(numbers);
	return (1);
}
