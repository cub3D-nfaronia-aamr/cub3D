#include "cub3d.h"

/* Frees everything the parser and MiniLibX allocated. Does not exit. */
void	free_game(t_data *data)
{
	free_map(&data->map);
	free_config(&data->config);
	if (data->mlx.img && data->mlx.mlx)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	if (data->mlx.win && data->mlx.mlx)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	if (data->mlx.mlx)
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
	}
	data->mlx.img = NULL;
	data->mlx.win = NULL;
	data->mlx.mlx = NULL;
}

/* ESC key or the window's close button. */
int	game_close(void *param)
{
	free_game((t_data *)param);
	exit(EXIT_SUCCESS);
	return (0);
}

/* Opens the window and the image the whole frame is drawn into. */
void	initialize(t_data *data)
{
	t_mlx	*g;

	g = &data->mlx;
	g->mlx = mlx_init();
	if (g->mlx)
		g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3D");
	if (g->win)
		g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->img)
	{
		error_msg("Failed to start MiniLibX.");
		free_game(data);
		exit(EXIT_FAILURE);
	}
	g->addr = mlx_get_data_addr(g->img, &g->bits_per_pixel,
			&g->size_line, &g->endian);
}

/* Draws the frame on start-up and whenever the window needs repainting. */
int	render(void *param)
{
	draw_map((t_data *)param);
	return (0);
}

/* Runs every frame: move by the keys being held, then draw. */
int	game_loop(void *param)
{
	move_player((t_data *)param);
	draw_map((t_data *)param);
	return (0);
}
