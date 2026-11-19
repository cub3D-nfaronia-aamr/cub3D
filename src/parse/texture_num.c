/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/19 00:22:04 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

static int	rgb_data(t_config *config, char **numbers, char type)
{
	int	x;
	int	y;
	int	z;
	int	num;

	x = 0;
	while (numbers[x])
	{
		y = 0;
		z = y;
		while (numbers[x][z] == '0')
			z++;
		while (numbers[x][y])
		{
			if (!(numbers[x][y] >= '0' && numbers[x][y] <= '9'))
			{
				printf("Error\nThere is an incorrect number.");
				return (0);
			}
			y++;
			if (y - z > 3)
			{
				printf("Error\nThe color number is greater than 255.");
				return (0);
			}
		}
		x++;
	}
	x = 0;
	while (numbers[x])
	{
		num = ft_atoi(numbers[x]);
		if (num > 255)
		{
			printf("Error\nThe color number is greater than 255.");
			return (0);
		}
		x++;
	}
	if (type == 'F')
	{
		if (config->floor.r == -1 && config->floor.g == -1
			&& config->floor.b == -1)
		{
			config->floor.r = ft_atoi(numbers[0]);
			config->floor.g = ft_atoi(numbers[1]);
			config->floor.b = ft_atoi(numbers[2]);
		}
		else
		{
			printf("Error\nmore than one value for (F)");
			return (0);
		}
	}
	else
	{
		if (config->ceiling.r == -1 && config->ceiling.g == -1
			&& config->ceiling.b == -1)
		{
			config->ceiling.r = ft_atoi(numbers[0]);
			config->ceiling.g = ft_atoi(numbers[1]);
			config->ceiling.b = ft_atoi(numbers[2]);
		}
		else
		{
			printf("Error\nmore than one value for (C)");
			return (0);
		}
	}
	return (1);
}

char	**remove_spases(char **numbers)
{
	int		x;
	int		y;
	int		start;
	int		end;
	char	*new;

	x = 0;
	while (numbers[x])
	{
		start = 0;
		end = 0;
		y = 0;
		while (numbers[x][y] == ' ' || numbers[x][y] == '\t')
			y++;
		start = y;
		while (numbers[x][y] != '\0')
			y++;
		end = y - 1;
		while (end  >= start &&
			(numbers[x][end] == ' ' || numbers[x][end] == '\t'))
			--end;
		new = ft_substr(numbers[x], start, end - start + 1);
		if (!new)
		{
			free_split(numbers);
			return (NULL);
		}
		free(numbers[x]);
		numbers[x] = new;
		x++;
	}
	return (numbers);
}

static int	split_count(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	texture_num(t_config *config, char *line, int *i)
{
	int		start;
	char	*nums;
	char	**numbers;
	char	type;
	int		c;

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
	while (line[*i] && line[*i] != '\n' && line[*i] != '\r')
		(*i)++;
	nums = ft_substr(line, start, *i - start);
	if (!nums)
		return (0);
	c = 0;
	while (nums[c])
	{
		if (nums[0] == ',')
		{
			printf("Error\nInvalid line (there is , in beginning)");
			free(nums);
			return (0);
		}
		if ((nums[c] == ',' && nums[c + 1] == ',')
			|| (nums[c] == ',' && nums[c + 1] == '\0'))
		{
			printf("Error\nInvalid line (there is more than , in line)");
			free(nums);
			return (0);
		}
		c++;
	}
	numbers = ft_split(nums, ',');
	free(nums);
	if (!numbers)
		return (0);
	if (split_count(numbers) != 3)
	{
		printf("Error\nThere is an error in the color inputs");
		free_split(numbers);
		return (0);
	}
	numbers = remove_spases(numbers);
	if (numbers == NULL)
		return (0);
	c = 0;
	while (numbers[c])
	{
		if (numbers[c][0] == '\0')
		{
			printf("Error\nEmpty color number.");
			free_split(numbers);
			return (0);
		}
		c++;
	}
	if (!(rgb_data(config, numbers, type)))
	{
		free_split(numbers);
		return (0);
	}
	free_split(numbers);
	return (1);
}
