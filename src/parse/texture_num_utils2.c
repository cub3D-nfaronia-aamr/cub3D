/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_num_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 02:45:49 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	split_count(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*trim_spaces(char *numbers)
{
	int		start;
	int		end;
	char	*new;

	start = 0;
	while (numbers[start] == ' ' || numbers[start] == '\t')
		start++;
	end = ft_strlen(numbers) - 1;
	while (end >= start && (numbers[end] == ' ' || numbers[end] == '\t'))
		--end;
	new = ft_substr(numbers, start, end - start + 1);
	return (new);
}

char	**remove_spaces(char **numbers)
{
	int		x;
	char	*new;

	x = 0;
	while (numbers[x])
	{
		new = trim_spaces(numbers[x]);
		if (!new)
		{
			error_msg("Invalid malloc.");
			free_split(numbers);
			return (NULL);
		}
		free(numbers[x]);
		numbers[x] = new;
		x++;
	}
	return (numbers);
}

char	*get_color_line(char *line, int *i)
{
	int		start;
	char	*nums;

	start = *i;
	while (line[*i] && line[*i] != '\n' && line[*i] != '\r')
		(*i)++;
	nums = ft_substr(line, start, *i - start);
	return (nums);
}
