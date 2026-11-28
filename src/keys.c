#include "cub3d.h"

static void	set_key(t_keys *keys, int keycode, int value)
{
	if (keycode == W)
		keys->w = value;
	else if (keycode == A)
		keys->a = value;
	else if (keycode == S)
		keys->s = value;
	else if (keycode == D)
		keys->d = value;
	else if (keycode == LEFT)
		keys->left = value;
	else if (keycode == RIGHT)
		keys->right = value;
}

int	key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == ESC)
		game_close(data);
	set_key(&data->keys, keycode, 1);
	return (0);
}

int	key_release(int keycode, void *param)
{
	set_key(&((t_data *)param)->keys, keycode, 0);
	return (0);
}
