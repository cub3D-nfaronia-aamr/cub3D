#include "../include/cub3d.h"

#define MAP_TILE_SIZE 100
#define PLAYER_SIZE 10

static int	tile_color(char tile)
{
	if (tile >= '1')
		return (0x808080);
	return (0x202020);
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

void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.map_height)
	{
		x = 0;
		while (x < data->map.map_width)
		{
			draw_tile(data, x, y, tile_color(data->map.map_data[y][x]));
			x++;
		}
		y++;
	}
	draw_player(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
}
