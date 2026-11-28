/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:18:02 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 14:57:42 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		error_msg("Usage: ./cub3d map.cub");
		return (1);
	}
	ft_bzero(&data, sizeof(t_data));
	if (!open_file(&data.map, &data.config, &data.map.player, argv[1]))
		return (1);
	initialize(&data);
	mlx_expose_hook(data.mlx.win, render, &data);
	mlx_hook(data.mlx.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx.mlx, game_loop, &data);
	mlx_hook(data.mlx.win, 17, 0, game_close, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
