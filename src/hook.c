/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:18:15 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 14:33:56 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_position(t_data *data, double x, double y)
{
	int		len;
	int		i;
	int		j;
	double	px;
	double	py;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			px = x + (i - 1) * RADIUS;
			py = y + (j - 1) * RADIUS;
			if (px < 0 || py < 0 || (int)py >= data->map.map_height)
				return (0);
			len = ft_strlen(data->map.map_data[(int)py]);
			if (px >= len)
				return (0);
			if (data->map.map_data[(int)py][(int)px] == '1'
				|| data->map.map_data[(int)py][(int)px] == ' ')
				return (0);
		}
	}
	return (1);
}

void	move_player(t_data *data, double movex, double movey)
{
	double	newx;
	double	newy;

	newx = data->map.player.x + movex;
	if (is_valid_position(data, newx, data->map.player.y))
		data->map.player.x = newx;
	newy = data->map.player.y + movey;
	if (is_valid_position(data, data->map.player.x, newy))
		data->map.player.y = newy;
}

void	rotation_player(t_data *data, double rotation_speed)
{
	double		newdirx;
	double		newdiry;
	t_player	*p;

	p = &data->map.player;
	newdirx = p->x_direction * cos(rotation_speed)
		- p->y_direction * sin(rotation_speed);
	newdiry = p->x_direction * sin(rotation_speed)
		+ p->y_direction * cos(rotation_speed);
	p->x_direction = newdirx;
	p->y_direction = newdiry;
	p->angle += rotation_speed;
	p->angle = fmod(p->angle, 2 * M_PI);
	if (p->angle < 0)
		p->angle += 2 * M_PI;
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == ESC)
		clean_exit(data);
	if (keycode == W)
		data->keys.w = 1;
	if (keycode == S)
		data->keys.s = 1;
	if (keycode == A)
		data->keys.a = 1;
	if (keycode == D)
		data->keys.d = 1;
	if (keycode == LEFT)
		data->keys.left = 1;
	if (keycode == RIGHT)
		data->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == W)
		data->keys.w = 0;
	if (keycode == S)
		data->keys.s = 0;
	if (keycode == A)
		data->keys.a = 0;
	if (keycode == D)
		data->keys.d = 0;
	if (keycode == LEFT)
		data->keys.left = 0;
	if (keycode == RIGHT)
		data->keys.right = 0;
	return (0);
}

int	game_loop(t_data *data)
{
	t_player	*p;

	p = &data->map.player;
	if (data->keys.w)
		move_player(data, (p->x_direction * MOVE),
			(p->y_direction * MOVE));
	if (data->keys.s)
		move_player(data, (-p->x_direction * MOVE),
			(-p->y_direction * MOVE));
	if (data->keys.a)
		move_player(data, (p->y_direction * MOVE),
			(-p->x_direction * MOVE));
	if (data->keys.d)
		move_player(data, (-p->y_direction * MOVE),
			(p->x_direction * MOVE));
	if (data->keys.left)
		rotation_player(data, -ROTATION);
	if (data->keys.right)
		rotation_player(data, ROTATION);
	return (0);
}

int	expose_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data)
		return (0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}
