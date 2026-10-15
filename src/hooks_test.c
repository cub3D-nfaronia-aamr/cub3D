#include "cub3d.h"

const int	g_world_map[MAP_HEIGHT][MAP_WIDTH] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static void	cleanup_and_exit(t_cub3d *f)
{
	if (f->img.img)
		mlx_destroy_image(f->mlx, f->img.img);
	if (f->win)
		mlx_destroy_window(f->mlx, f->win);
//	free_map(&f->map);
//	mlx_destroy_display(f->mlx);
	if (f->mlx)
		free(f->mlx);
	exit(0);
}

static void	draw_map(t_cub3d *f)
{
	int	x;
	int	y;
	int	cell_x;
	int	cell_y;

	cell_y = 0;
	while (cell_y < MAP_HEIGHT)
	{
		cell_x = 0;
		while (cell_x < MAP_WIDTH)
		{
			if (g_world_map[cell_y][cell_x] > 0)
			{
				y = 0;
				while (y < CELL_SIZE)
				{
					x = 0;
					while (x < CELL_SIZE)
					{
						mlx_pixel_put(f->mlx, f->win,
							cell_x * CELL_SIZE + x,
							cell_y * CELL_SIZE + y, 0x808080);
						x++;
					}
					y++;
				}
			}
			cell_x++;
		}
		cell_y++;
	}
}

int	draw_dot(t_cub3d *f)
{
	int	x;
	int	y;

	y = 0;
	while (y < DOT_SIZE)
	{
		x = 0;
		while (x < DOT_SIZE)
		{
			mlx_pixel_put(f->mlx, f->win, f->x + x, f->y + y, 0xFFFFFF);
			x++;
		}
		y++;
	}
	return (0);
}

int	draw_scene(t_cub3d *f)
{
	mlx_clear_window(f->mlx, f->win);
	draw_map(f);
	draw_dot(f);
	return (0);
}

static int	can_move_to(int x, int y)
{
	int	left;
	int	right;
	int	top;
	int	bottom;

	left = x / CELL_SIZE;
	right = (x + DOT_SIZE - 1) / CELL_SIZE;
	top = y / CELL_SIZE;
	bottom = (y + DOT_SIZE - 1) / CELL_SIZE;
	if (x < 0 || y < 0 || right >= MAP_WIDTH || bottom >= MAP_HEIGHT)
		return (0);
	if (g_world_map[top][left] > 0 || g_world_map[top][right] > 0
		|| g_world_map[bottom][left] > 0
		|| g_world_map[bottom][right] > 0)
		return (0);
	return (1);
}

int	on_key(int key, void *p)
{
	t_cub3d	*f;
	int		new_x;
	int		new_y;

	f = (t_cub3d *)p;
	if (key == KEY_ESC)
		cleanup_and_exit(f);
	new_x = f->x;
	new_y = f->y;
	if (key == 'w' || key == 65362)
		new_y -= 5;
	if (key == 's' || key == 65364)
		new_y += 5;
	if (key == 'a' || key == 65361)
		new_x -= 5;
	if (key == 'd' || key == 65363)
		new_x += 5;
	if (can_move_to(new_x, new_y))
	{
		f->x = new_x;
		f->y = new_y;
	}
	draw_scene(f);
	return (0);
}

int	on_close(void *p)
{
	cleanup_and_exit((t_cub3d *)p);
	return (0);
}
