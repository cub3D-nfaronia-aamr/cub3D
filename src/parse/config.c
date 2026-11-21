/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/21 03:14:46 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config(t_config *config)
{
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
	config->floor.r = -1;
	config->floor.g = -1;
	config->floor.b = -1;
	config->ceiling.r = -1;
	config->ceiling.g = -1;
	config->ceiling.b = -1;
}

void	free_config(t_config *config)
{
	free(config->no);
	free(config->so);
	free(config->we);
	free(config->ea);
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
}

int	not_empty_config(t_config *config)
{
	if (config->no == NULL || config->so == NULL
		|| config->we == NULL || config->ea == NULL
		|| config->floor.r == -1 || config->floor.g == -1
		|| config->floor.b == -1 || config->ceiling.r == -1
		|| config->ceiling.g == -1 || config->ceiling.b == -1)
		return (0);
	return (1);
}
