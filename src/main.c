/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:18:02 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/19 03:54:12 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	initialize(t_data *data)
{
	ft_bzero(&data->mlx, sizeof(t_mlx));
	data->mlx.mlx = mlx_init();
	if (data->mlx.mlx == NULL)
		error("Error\nfails to set up the connection to the graphical system\n");
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIDTH, HEIGHT, "game");
	if (data->mlx.win == NULL)
		error("Error\nfails to create a new window\n");
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	if (!data->mlx.img)
		error("Error\nfails to create a new image\n");
	data->mlx.addr = mlx_get_data_addr(data->mlx.img,
			&data->mlx.bits_per_pixel, &data->mlx.size_line, &data->mlx.endian);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (printf("Error\nUsage: ./cub3d map.cub\n"), 1);
	ft_bzero(&data, sizeof(t_data));
	if (!open_file(&data.map, &data.config, &data.map.player, argv[1]))
		return (1);
	initialize(&data);
	mlx_expose_hook(data.mlx.win, expose_hook, &data);
	mlx_key_hook(data.mlx.win, key_hook, &data);
	mlx_hook(data.mlx.win, 17, 0, close_window, &data);
	mlx_loop(data.mlx.mlx);
}
