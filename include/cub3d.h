/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamr <aamr@student.42amman.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:18:24 by nfaronia          #+#    #+#             */
/*   Updated: 2026/10/16 23:13:28 by aamr             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <string.h>

# define WIDTH 1000
# define HEIGHT 800
# define ESC 65307
# define PI 3.14159

typedef struct s_player
{
	double	x;
	double	y;
	double	xd;
	double	yd;
	double	angle;
}	t_player;

typedef struct s_map
{
	char		**map_data;
	int			map_width;
	int			map_height;
	t_player	player;
}	t_map;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_color	floor;
	t_color	ceiling;
}	t_config;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;

	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_mlx;

typedef struct s_data
{
	t_config	config;
	t_map		map;
	t_mlx		mlx;
}	t_data;

//hook.c
int		key_hook(int keycode, void *param);
int		expose_hook(void *param);

//utils.c
void	error(char *str);
void	clean_exit(t_mlx *game);
int		close_window(void *param);
void	my_mlx_pixel_put(t_mlx *image, int x, int y, int color);

//parse
//parser.c
void	open_file(t_map *map, t_config *config, t_player *player);
void	map_data(t_map *map, char *line, int *i, int num_line);
void	find_player(t_map *map, t_player *player);

//texture.c
void	texture_char(t_config *config, char *line, int *i);
void	texture_num(t_config *config, char *line, int *i);


//draw_map.c
void	draw_map(t_data *data);

#endif
