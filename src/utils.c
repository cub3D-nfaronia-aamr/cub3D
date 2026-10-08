/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:32:55 by nfaronia          #+#    #+#             */
/*   Updated: 2026/10/04 14:32:56 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error(char *str)
{
	printf("Error : %s\n", str);
	exit(EXIT_FAILURE);
}

void	clean_exit(t_mlx *game)
{
	if (game == NULL)
		exit(EXIT_SUCCESS);
	if (game->img && game->mlx)
	{
		mlx_destroy_image(game->mlx, game->img);
		game->img = NULL;
	}
	if (game->win && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	exit(EXIT_SUCCESS);
}

int	close_window(void *param)
{
	t_mlx	*game;

	game = (t_mlx *)param;
	clean_exit(game);
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
