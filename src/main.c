/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:18:02 by nfaronia          #+#    #+#             */
/*   Updated: 2026/10/08 17:27:36 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize(t_mlx *game)
{
	ft_bzero(game, sizeof(t_mlx));
	game->mlx = mlx_init();
	if (WIDTH <= 0 || HEIGHT <= 0)
	{
		printf("Error: Invalid window dimensions\n");
		close_window(game);
	}
	if (game->mlx == NULL)
		error("fails to set up the connection to the graphical system");
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "game");
	if (game->win == NULL)
		error("fails to create a new window");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		error("fails to create a new image");
	game->addr = mlx_get_data_addr(game->img,
			&game->bits_per_pixel, &game->size_line, &game->endian);
}

int	main(void)
{
	t_map		map;
	t_config	config;
	t_player	player;
	int			i;

	ft_bzero(&map, sizeof(t_map));
	ft_bzero(&config, sizeof(t_config));
	ft_bzero(&player, sizeof(t_player));

	open_file(&map, &config, &player);

	printf("========== TEXTURES ==========\n");
	printf("NO: %s\n", config.no);
	printf("SO: %s\n", config.so);
	printf("WE: %s\n", config.we);
	printf("EA: %s\n", config.ea);

	printf("\n========== RGB ==========\n");
	printf("F: %d,%d,%d\n",
		config.floor.r,
		config.floor.g,
		config.floor.b);
	printf("C: %d,%d,%d\n",
		config.ceiling.r,
		config.ceiling.g,
		config.ceiling.b);

	printf("\n========== MAP ==========\n");
	printf("Width: %d\n", map.map_width);
	printf("Height: %d\n", map.map_height);

	i = 0;
	while (map.map_data && map.map_data[i])
	{
		printf("%s\n", map.map_data[i]);
		i++;
	}

	printf("\n========== PLAYER ==========\n");
	printf("x: %f\n", player.x);
	printf("y: %f\n", player.y);
	printf("direction x: %f\n", player.x_direction);
	printf("direction y: %f\n", player.y_direction);
	printf("angle: %f\n", player.angle);

	return (0);
}



/*int	main(int argc, char **argv)
{
	t_mlx	game;

	(void)argc;
	(void)argv;
	initialize(&game);
	mlx_expose_hook(game.win, expose_hook, &game);
	mlx_key_hook(game.win, key_hook, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}*/