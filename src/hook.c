/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:18:15 by nfaronia          #+#    #+#             */
/*   Updated: 2026/10/04 14:22:04 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, t_mlx *game)
{
	if (keycode == ESC)
		clean_exit(game);
	return (0);
}

int	expose_hook(void *param)
{
	t_mlx	*game;

	game = (t_mlx *)param;
	if (!game)
		return (0);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}