/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:18:15 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/19 03:53:35 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	expose_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (!data)
		return (0);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win, data->mlx.img, 0, 0);
	return (0);
}
