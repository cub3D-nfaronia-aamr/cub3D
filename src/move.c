#include "cub3d.h"

/* Anything outside the map, a space, or a '1' counts as wall. */
static int	is_wall(t_map *map, double x, double y)
{
	int	mx;
	int	my;

	if (x < 0 || y < 0)
		return (1);
	mx = (int)x;
	my = (int)y;
	if (my >= map->map_height || !map->map_data[my])
		return (1);
	if (mx >= (int)ft_strlen(map->map_data[my]))
		return (1);
	return (map->map_data[my][mx] != '0');
}

/*
** The player is a small square of half-size RADIUS. Each axis is tried
** on its own, so walking into a wall at an angle slides along it.
*/
static void	try_move(t_map *map, double dx, double dy)
{
	t_player	*p;
	double		nx;
	double		ny;

	p = &map->player;
	nx = p->x + dx;
	if (!is_wall(map, nx - RADIUS, p->y - RADIUS)
		&& !is_wall(map, nx + RADIUS, p->y - RADIUS)
		&& !is_wall(map, nx - RADIUS, p->y + RADIUS)
		&& !is_wall(map, nx + RADIUS, p->y + RADIUS))
		p->x = nx;
	ny = p->y + dy;
	if (!is_wall(map, p->x - RADIUS, ny - RADIUS)
		&& !is_wall(map, p->x + RADIUS, ny - RADIUS)
		&& !is_wall(map, p->x - RADIUS, ny + RADIUS)
		&& !is_wall(map, p->x + RADIUS, ny + RADIUS))
		p->y = ny;
}

/* y points down, so a positive angle turns right (clockwise on screen). */
static void	rotate(t_player *p, double delta)
{
	p->angle = fmod(p->angle + delta, 2 * PI);
	p->xd = cos(p->angle);
	p->yd = sin(p->angle);
}

/*
** W/S: forward/back. A/D: step left/right. Arrows: turn.
** The player's right-hand side is (-yd, xd), the same as the camera plane.
*/
void	move_player(t_data *data)
{
	t_map		*m;
	t_player	*p;

	m = &data->map;
	p = &m->player;
	if (data->keys.w)
		try_move(m, p->xd * MOVE, p->yd * MOVE);
	if (data->keys.s)
		try_move(m, -p->xd * MOVE, -p->yd * MOVE);
	if (data->keys.a)
		try_move(m, p->yd * MOVE, -p->xd * MOVE);
	if (data->keys.d)
		try_move(m, -p->yd * MOVE, p->xd * MOVE);
	if (data->keys.left)
		rotate(p, -ROTATION);
	if (data->keys.right)
		rotate(p, ROTATION);
}
