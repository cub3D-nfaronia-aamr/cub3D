#include "../include/cub3d.h"

void	draw(t_data *data);
int		move_key(int keycode, void *param);
int		test_expose_hook(void *param);

int		close_hook(void *param);


int	init_win(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		return (1);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "cub3d");
	if (mlx->win == NULL)
		return (1);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (mlx->img == NULL)
		return (1);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->size_line, &mlx->endian);
	return (0);
}

int	main(void)
{
	t_data	test;

	static char	*g_world_map[] =
	{
	"111111111111111111111111",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000222220000030303001",
	"100000200020000000000001",
	"100000200020000030003001",
	"100000200020000000000001",
	"100000220220000030303001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"100000000000000000000001",
	"144444444000000000000001",
	"140400004000000000000001",
	"140000054000000000000001",
	"140400004000000000000001",
	"140444444000000000000001",
	"140000000000000000000001",
	"144444444000000000000001",
	"111111111111111111111111",
	NULL
	};

	// Initialize the test data structure - set all fields to zero!! why ?!
	ft_bzero(&test, sizeof(t_data));

	test.map.map_data = g_world_map;
	test.map.map_width = 24;
	test.map.map_height = 24;
	test.map.player.x = 4;
	test.map.player.y = 4;
	test.map.player.xd = 0;
	test.map.player.yd = 1;
	test.map.player.angle = 90;

	if (init_win(&test.mlx))
		return (1);
	draw_map(&test);
	mlx_expose_hook(test.mlx.win, test_expose_hook, &test);
	mlx_key_hook(test.mlx.win, key_hook, &test);
	mlx_hook(test.mlx.win, 17, 0, close_hook, &test);
	mlx_loop(test.mlx.mlx);
	return (0);
}
