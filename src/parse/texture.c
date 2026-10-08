/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/10/08 16:42:06 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_path(char *line, int *i, int *start)
{
	*i = *i + 2;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	*start = *i;
	while (line[*i] && line[*i] != '\n')
		(*i)++;
}

void	texture_char(t_config *config, char *line, int *i)
{
	int		start;
	char	**path;

	start = 0;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	if (ft_strncmp(line + *i, "NO", 2) == 0
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
		path = &config->no;
	else if (ft_strncmp(line + *i, "SO", 2) == 0
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
		path = &config->so;
	else if (ft_strncmp(line + *i, "WE", 2) == 0
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
		path = &config->we;
	else if (ft_strncmp(line + *i, "EA", 2) == 0
		&& (line[*i + 2] == ' ' || line[*i + 2] == '\t'))
		path = &config->ea;
	else
		return ;
	get_path(line, i, &start);
	*path = ft_substr(line, start, *i - start);
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

void	texture_num(t_config *config, char *line, int *i)
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
		return ;
	(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	start = *i;
	while (line[*i] && line[*i] != '\n')
		(*i)++;
	num = ft_substr(line, start, *i - start);
	if (!num)
		return ;
	numbers = ft_split(num, ',');
	free(num);
	if (!numbers)
		return ;
	rgb_data(config, numbers, type);
	free_split(numbers);
}
