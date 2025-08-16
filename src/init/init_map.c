/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:06:21 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/16 14:59:27 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	bzero_map(t_map_elements *map)
{
	if (!map)
		return;
	map->floor = 0;
	map->ceiling = 0;
	map->map = NULL;
	map->north = NULL;
	map->south = NULL;
	map->west = NULL;
	map->east = NULL;
	map->cols = 0;
	map->rows = 0;
	bzero_vector(&map->player);
	bzero_vector(&map->plane);
}

/**
 * @brief responsible for initializing floor and ceiling colors, and textures.
 *
 * @param map map struct
 * @param fd map fd
 * @return int 0 on success, errno on failure.
 */
int	init_map_elements(t_map_elements *map,int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		errno = ENOMEM;
		return (-1);
	}
	while (line && !is_map_content(line))
	{
		trim_whitespace(line);
		if(*line)
			errno = load_data(map, line);
		free(line);
		if (errno)
			return (-1);
		line = get_next_line(fd);
	}
	if (line)
		map->firstline  = line;
	return (0);
}
int	init_map_content(t_map_elements *map,int fd);

/**
 * @brief map loader entry point. returns a fully initialized map
 *
 * @param fd fd to the map file.
 * @param map pointer to the map elements struct to fill.
 * @return int 0 on success, errno on failure.
 */
int	init_map(int fd,t_map_elements *map)
{
	bzero_map(map);
	if ((init_map_elements(map, fd) == -1
		|| init_map_content(map, fd) == -1) && !errno)
	{
			errno =  ENOMEM;
			clean_map(map);
	}
	close(fd);
	return (errno);
}
