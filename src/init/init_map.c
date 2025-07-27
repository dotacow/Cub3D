/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:06:21 by yokitane          #+#    #+#             */
/*   Updated: 2025/07/27 21:35:06 by yokitane         ###   ########.fr       */
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
	map->columns = 0;
	map->rows = 0;
	bzero_vector(&map->player);
	bzero_vector(&map->plane);
}
int	init_map_elements(t_map_elements *map,int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)

}
int	init_map_content(t_map_elements *map,int fd);

t_map_elements	init_map(int fd)
{
	t_map_elements	map;

	bzero_map(&map);
	if ((init_map_elements(&map, fd) == -1
		|| init_map_content(&map, fd) == -1) && !errno)
			errno =  ENOMEM;
	return (map);
}
