#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include "mlx.h"

# define WIN_W 1200
# define WIN_H 800
# define KEY_ESC 65307
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define CELL_SIZE 10
# define DOT_SIZE 5

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_cub3d
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		x;
	int		y;
//	t_map	map;
//	t_cam	cam;
}	t_cub3d;

int	on_close(void *p);
int	on_key(int key, void *p);
int	draw_dot(t_cub3d *f);
int	draw_scene(t_cub3d *f);

void	clean_img(t_cub3d *f);

extern const int	g_world_map[MAP_HEIGHT][MAP_WIDTH];

#endif