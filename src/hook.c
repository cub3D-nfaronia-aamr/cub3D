#include "../include/cub3d.h"

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

/*
** angle is in radians, screen space (y points down):
** 0 = right (E), PI/2 = down (S), PI = left (W), 3PI/2 = up (N).
** Negative delta turns left (counter-clockwise on screen).
*/
static void	rotate_player(t_player *player, double delta)
{
	player->angle = fmod(player->angle + delta, 2 * PI);
	if (player->angle < 0)
		player->angle += 2 * PI;
	player->xd = cos(player->angle);
	player->yd = sin(player->angle);
}

int	move_key(int keycode, void *param)
{
	t_data	*data;
	double	x;
	double	y;

	data = (t_data *)param;
	if (keycode == ESC)
		clean_exit(&data->mlx);
	x = data->map.player.x;
	y = data->map.player.y;

	if (keycode == 65361)
		x -= 0.5;
	else if (keycode == 65363)
		x += 0.5;
	else if (keycode == 65362)
		y -= 0.5;
	else if (keycode == 65364)
		y += 0.5;
	else if (keycode == KEY_W)
	{
		x += data->map.player.xd * MOVE_STEP;
		y += data->map.player.yd * MOVE_STEP;
	}
	else if (keycode == KEY_S)
	{
		x -= data->map.player.xd * MOVE_STEP;
		y -= data->map.player.yd * MOVE_STEP;
	}
	else if (keycode == KEY_A)
		rotate_player(&data->map.player, -ROT_STEP);
	else if (keycode == KEY_D)
		rotate_player(&data->map.player, ROT_STEP);
	if (can_move_to(data, x, y))
	{
		data->map.player.x = x;
		data->map.player.y = y;
	}
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
