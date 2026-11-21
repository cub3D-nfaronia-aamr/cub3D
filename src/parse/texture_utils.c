/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaronia <nfaronia@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 09:09:26 by nfaronia          #+#    #+#             */
/*   Updated: 2026/11/20 15:28:12 by nfaronia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	correct_path(char *path)
{
	int	fd;

	fd = open(path, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		error_msg("Path is a directory");
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error_msg("cannot open path.");
		return (0);
	}
	close(fd);
	return (1);
}
