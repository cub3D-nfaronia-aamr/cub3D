/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:32:55 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 03:21:33 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char *str)
{
	printf("Error : %s\n", str);
	exit(EXIT_FAILURE);
}

void	clean_exit(t_data *data)
{
	if (data == NULL)
		exit(EXIT_SUCCESS);
	if (data->mlx.img && data->mlx.mlx)
	{
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
		data->mlx.img = NULL;
	}
	if (data->mlx.win && data->mlx.mlx)
	{
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		data->mlx.win = NULL;
	}
	if (data->mlx.mlx)
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
		data->mlx.mlx = NULL;
	}
	free_config(&data->config);
	free_map(&data->map);
	exit(EXIT_SUCCESS);
}

int	close_window(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clean_exit(data);
	return (0);
}

void	my_mlx_pixel_put(t_mlx *image, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = image->addr + (y * image->size_line
				+ x * (image->bits_per_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}
