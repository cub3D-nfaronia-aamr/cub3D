/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcolor_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 03:02:31 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_number(char *str)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (str[z] == '0')
		z++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i - z > 3)
		return (0);
	if (ft_atoi(str) > 255)
		return (0);
	return (1);
}

static int	check_rgb(char **numbers)
{
	int	i;

	i = 0;
	while (numbers[i])
	{
		if (!check_number(numbers[i]))
		{
			error_msg("Invalid color number.");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	set_rgb(t_config *config, char **numbers, char type)
{
	if (type == 'F' && config->floor.r == -1 && config->floor.g == -1
		&& config->floor.b == -1)
	{
		config->floor.r = ft_atoi(numbers[0]);
		config->floor.g = ft_atoi(numbers[1]);
		config->floor.b = ft_atoi(numbers[2]);
		return (1);
	}
	if (type == 'C' && config->ceiling.r == -1 && config->ceiling.g == -1
		&& config->ceiling.b == -1)
	{
		config->ceiling.r = ft_atoi(numbers[0]);
		config->ceiling.g = ft_atoi(numbers[1]);
		config->ceiling.b = ft_atoi(numbers[2]);
		return (1);
	}
	error_msg("Duplicate color.");
	return (0);
}

int	rgb_data(t_config *config, char **numbers, char type)
{
	if (!check_rgb(numbers))
		return (0);
	if (!set_rgb(config, numbers, type))
		return (0);
	return (1);
}
