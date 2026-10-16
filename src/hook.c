#include "cub3d.h"

static int	can_move_to(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || y < 0)
		return (0);
	map_x = (int)x;
	map_y = (int)y;
	if (map_x >= data->map.map_width || map_y >= data->map.map_height)
		return (0);
	return (data->map.map_data[map_y][map_x] == '0');
}

int	move_key(int keycode, void *param)
{
	t_data	*data;
	double	x;
	double	y;
	double 	xd;
	double 	yd;

	data = (t_data *)param;
	if (keycode == ESC)
		clean_exit(&data->mlx);
	x = data->map.player.x;
	y = data->map.player.y;
	xd = data->map.player.xd;
	yd = data->map.player.yd;

	if (keycode == 65361)
		x -= 1;
	else if (keycode == 65363)
		x += 1;
	else if (keycode == 65362)
		y -= 1;
	else if (keycode == 65364)
		y += 1;
	else if (keycode == 97)
	{
		xd -= 0.1 * data->map.player.yd;
		yd += 0.1 * data->map.player.xd;
		printf("xd: %f, yd: %f\n", xd, yd);
	}
	else if (keycode == 100)
	{
		xd += 0.1 * data->map.player.yd;
		yd -= 0.1 * data->map.player.xd;
		printf("xd: %f, yd: %f\n", xd, yd);
	}
	if (can_move_to(data, x, y))
	{
		data->map.player.x = x;
		data->map.player.y = y;
	}
	data->map.player.xd = xd;
	data->map.player.yd = yd;
	return (0);
}

int	close_hook(void *param)
{
	clean_exit(&((t_data *)param)->mlx);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	if (keycode == ESC)
		clean_exit(&((t_data *)param)->mlx);
	move_key(keycode, param);
	draw_map((t_data *)param);
	return (0);
}

int	test_expose_hook(void *param)
{
	
	draw_map((t_data *)param);
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
