/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 11:09:51 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' || line[i] == '\t'
				|| line[i] == '\n' || line[i] == '\r'))
			return (0);
		i++;
	}
	return (1);
}

int	is_direction_line(char *line)
{
	return ((ft_strncmp(line, "NO", 2) == 0
			|| ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0
			|| ft_strncmp(line, "EA", 2) == 0)
		&& (line[2] == ' ' || line[2] == '\t'));
}

int	is_color_line(char *line)
{
	return ((line[0] == 'F' || line[0] == 'C')
		&& (line[1] == ' ' || line[1] == '\t'));
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

int	fail_line(char *line)
{
	free(line);
	clear_gnl();
	return (0);
}
