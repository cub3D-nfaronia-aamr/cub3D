#include "../include/cub3d.h"

/*
** Raycasting: one ray per screen column.
** Coordinates are in tiles, with y pointing down.
** The camera plane is perpendicular to the direction (xd, yd) and points to
** the player's right. Its length (FOV_PLANE) sets the field of view.
*/

/* First grid line the ray crosses, and which way it steps on the grid. */
static void	init_step(t_player *p, t_ray *r)
{
	if (r->dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (p->x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - p->x) * r->delta_x;
	}
	if (r->dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (p->y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - p->y) * r->delta_y;
	}
}

/* camera_x goes from -1 (left edge of screen) to +1 (right edge). */
static void	init_ray(t_data *data, t_ray *r, int col)
{
	t_player	*p;
	double		camera_x;

	p = &data->map.player;
	camera_x = 2.0 * col / (double)WIDTH - 1.0;
	r->dir_x = p->xd + (-p->yd * FOV_PLANE) * camera_x;
	r->dir_y = p->yd + (p->xd * FOV_PLANE) * camera_x;
	r->map_x = (int)p->x;
	r->map_y = (int)p->y;
	r->delta_x = 1e30;
	if (r->dir_x != 0)
		r->delta_x = fabs(1.0 / r->dir_x);
	r->delta_y = 1e30;
	if (r->dir_y != 0)
		r->delta_y = fabs(1.0 / r->dir_y);
	init_step(p, r);
}

/*
** DDA: jump from one grid line to the next (whichever is closer)
** until the cell we enter is a wall. Stops if the ray leaves the map.
*/
static void	run_dda(t_data *data, t_ray *r)
{
	char	*row;

	r->hit = 0;
	while (!r->hit)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_y < 0 || r->map_y >= data->map.map_height)
			return ;
		row = data->map.map_data[r->map_y];
		if (r->map_x >= (int)ft_strlen(row))
			return ;
		if (row[r->map_x] != '0')
			r->hit = 1;
	}
}

/*
** side 0 = the ray crossed a vertical grid line (moving east or west).
** side 1 = it crossed a horizontal grid line (moving north or south).
** Above and below the wall is black (ceiling and floor).
*/
static void	draw_column(t_data *data, t_ray *r, int col)
{
	int	height;
	int	start;
	int	end;
	int	color;
	int	y;

	if (r->side == 0 && r->dir_x > 0)
		color = COL_EAST;
	else if (r->side == 0)
		color = COL_WEST;
	else if (r->dir_y > 0)
		color = COL_SOUTH;
	else
		color = COL_NORTH;
	height = (int)(HEIGHT / r->perp);
	start = HEIGHT / 2 - height / 2;
	end = HEIGHT / 2 + height / 2;
	y = -1;
	while (++y < HEIGHT)
	{
		if (y >= start && y < end)
			my_mlx_pixel_put(&data->mlx, col, y, color);
		else
			my_mlx_pixel_put(&data->mlx, col, y, 0x000000);
	}
}

/*
** perp is the distance measured perpendicular to the camera plane, not the
** straight-line distance. Using it is what avoids the fisheye effect.
*/
void	render_3d(t_data *data)
{
	t_ray	r;
	int		col;

	col = 0;
	while (col < WIDTH)
	{
		init_ray(data, &r, col);
		run_dda(data, &r);
		r.perp = 1e30;
		if (r.hit && r.side == 0)
			r.perp = r.side_x - r.delta_x;
		else if (r.hit)
			r.perp = r.side_y - r.delta_y;
		if (r.perp < 0.0001)
			r.perp = 0.0001;
		draw_column(data, &r, col);
		col++;
	}
}
