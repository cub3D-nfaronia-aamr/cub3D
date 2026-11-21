/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 02:58:18 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_commas(char *nums)
{
	int	c;

	if (nums[0] == ',')
	{
		error_msg("comma at beginning.");
		return (0);
	}
	c = 0;
	while (nums[c])
	{
		if ((nums[c] == ',' && nums[c + 1] == ',')
			|| (nums[c] == ',' && nums[c + 1] == '\0'))
		{
			error_msg("Invalid commas.");
			return (0);
		}
		c++;
	}
	return (1);
}

static int	check_empty(char **numbers)
{
	int	c;

	c = 0;
	while (numbers[c])
	{
		if (!numbers[c][0])
		{
			error_msg("Empty color number.");
			return (0);
		}
		c++;
	}
	return (1);
}

static int	check_rgb_input(t_config *config, char **numbers, char type)
{
	int	ret;

	if (split_count(numbers) != 3)
	{
		error_msg("Invalid color.");
		free_split(numbers);
		return (0);
	}
	numbers = remove_spaces(numbers);
	if (!numbers)
		return (0);
	if (!check_empty(numbers))
	{
		free_split(numbers);
		return (0);
	}
	ret = rgb_data(config, numbers, type);
	free_split(numbers);
	return (ret);
}

static int	process_rgb(t_config *config, char *nums, char type)
{
	char	**numbers;
	int		ret;

	if (!check_commas(nums))
	{
		free(nums);
		return (0);
	}
	numbers = ft_split(nums, ',');
	free(nums);
	if (!numbers)
	{
		error_msg("Invalid malloc");
		return (0);
	}
	ret = check_rgb_input(config, numbers, type);
	return (ret);
}

int	texture_num(t_config *config, char *line, int *i)
{
	char	*nums;
	char	type;
	int		r;

	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	type = line[*i];
	if ((type != 'F' && type != 'C')
		|| (line[*i + 1] != ' ' && line[*i + 1] != '\t'))
	{
		error_msg("Invalid color identifier.");
		return (0);
	}
	(*i)++;
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
	nums = get_color_line(line, i);
	if (!nums)
	{
		error_msg("Invalid malloc.");
		return (0);
	}
	r = process_rgb(config, nums, type);
	return (r);
}
