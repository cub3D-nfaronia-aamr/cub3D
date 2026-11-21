/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:18:02 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 14:45:18 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_ptr(t_data *data, void *ptr, char *msg)
{
	if (ptr == NULL)
	{
		error_msg(msg);
		clean_exit(data);
	}
}

void	initialize(t_data *data)
{
	ft_bzero(&data->mlx, sizeof(t_mlx));
	data->mlx.mlx = mlx_init();
	check_ptr(data, data->mlx.mlx,
		"fails to set up the connection to the graphical system");
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIDTH, HEIGHT, "game");
	check_ptr(data, data->mlx.win, "fails to create a new window");
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	check_ptr(data, data->mlx.img, "fails to create a new image");
	data->mlx.addr = mlx_get_data_addr(data->mlx.img,
			&data->mlx.bits_per_pixel, &data->mlx.size_line, &data->mlx.endian);
	check_ptr(data, data->mlx.addr, "fails to get data addr");
}

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
	mlx_expose_hook(data.mlx.win, expose_hook, &data);
	mlx_hook(data.mlx.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.mlx.win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx.mlx, game_loop, &data);
	mlx_hook(data.mlx.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
