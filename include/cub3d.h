/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:18:24 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 11:10:11 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <string.h>

# define WIDTH  1000
# define HEIGHT 800
# define ESC    65307
# define W      119
# define A      97
# define S      115
# define D      100
# define LEFT   65361
# define RIGHT  65363
# define UP     65362
# define DOWN   65364
# define PI     3.14159

typedef struct s_player
{
	double	x;
	double	y;
	double	x_direction;
	double	y_direction;
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
int		key_hook(int keycode, t_data *data);
int		expose_hook(void *param);

//utils.c
void	error(char *str);
void	clean_exit(t_data *data);
int		close_window(void *param);
void	my_mlx_pixel_put(t_mlx *image, int x, int y, int color);
int		is_empty_line(char *line);

//parse
//parser.c
int		count_map_line(int fd);
int		is_empty_line(char *line);
int		allow_char_map(char *line);
int		parse_file(t_map *map, t_config *config, int fd);
int		open_file(t_map *map, t_config *config, t_player *player, char *argv);
int		fail_line(char *line);


//config.c
void	init_config(t_config *config);
void	free_config(t_config *config);
int		not_empty_config(t_config *config);

//texture_char.c
int		correct_path(char *path);
int		texture_char(t_config *config, char *line, int *i);
int		validate_player(t_map *map, t_player *player);

//texture_num.c
int		texture_num(t_config *config, char *line, int *i);
int		rgb_data(t_config *config, char **numbers, char type);
void	free_split(char **str);
int		split_count(char **str);
char	**remove_spaces(char **numbers);
char	*get_color_line(char *line, int *i);

//player.c
int		count_players(t_map *map);
void	locate_player(t_map *map, t_player *player);

//map.c
void	init_map(t_map *map);
void	free_map(t_map *map);
char	*map_data(t_map *map, char *line, int num_line);
int		allocate_map(t_map *map, int num_line);


void	error_msg(char *msg);

int		is_direction_line(char *line);
int		is_color_line(char *line);
void	skip_spaces(char *line, int *i);

#endif