#include "../include/cub3d.h"

#define MAP_TILE_SIZE 10
#define PLAYER_SIZE 6
#define DIR_LINE_LEN 25

static int	tile_color(char tile)
{
	if (tile >= '1' && tile <= '9')
		return (0x808080);
	if (tile == '0' || tile == 'N' || tile == 'S'
		|| tile == 'E' || tile == 'W')
		return (0x202020);
	return (0x000000);
}

static void	draw_tile(t_data *data, int x, int y, int color)
{
	int	pixel_x;
	int	pixel_y;

	pixel_y = 0;
	while (pixel_y < MAP_TILE_SIZE)
	{
		pixel_x = 0;
		while (pixel_x < MAP_TILE_SIZE)
		{
			my_mlx_pixel_put(&data->mlx,
				x * MAP_TILE_SIZE + pixel_x,
				y * MAP_TILE_SIZE + pixel_y, color);
			pixel_x++;
		}
		pixel_y++;
	}
}

static void	draw_player(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->map.player.x * MAP_TILE_SIZE) - PLAYER_SIZE / 2;
	y = (int)(data->map.player.y * MAP_TILE_SIZE) - PLAYER_SIZE / 2;
	while (y < (int)(data->map.player.y * MAP_TILE_SIZE) + PLAYER_SIZE / 2)
	{
		x = (int)(data->map.player.x * MAP_TILE_SIZE) - PLAYER_SIZE / 2;
		while (x < (int)(data->map.player.x * MAP_TILE_SIZE)
			+ PLAYER_SIZE / 2)
		{
			my_mlx_pixel_put(&data->mlx, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

/* Line from the player's center in the direction it is facing. */
static void	draw_direction(t_data *data)
{
	double	cx;
	double	cy;
	int		i;

	cx = data->map.player.x * MAP_TILE_SIZE;
	cy = data->map.player.y * MAP_TILE_SIZE;
	i = 0;
	while (i < DIR_LINE_LEN)
	{
		my_mlx_pixel_put(&data->mlx, (int)(cx + data->map.player.xd * i),
			(int)(cy + data->map.player.yd * i), 0xFF0000);
		i++;
	}
}

/* 3D view fills the whole image; the minimap is then drawn on top of it. */
void	draw_map(t_data *data)
{
	int	x;
	int	y;

	render_3d(data);
	y = 0;
	while (y < data->map.map_height)
	{
		x = 0;
		while (x < data->map.map_width && data->map.map_data[y][x])
		{
			draw_tile(data, x, y, tile_color(data->map.map_data[y][x]));
			x++;
		}
		y++;
	}
	draw_player(data);
	draw_direction(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
