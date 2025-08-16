/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 23:05:46 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/16 17:34:47 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief reads the map content from the file descriptor and stores it in the map struct
 *
 * @param map
 * @param fd
 * @return int
 */
static int read_map(t_map_elements *map, int fd)
{
	while (map->firstline && is_map_content(map->firstline))
	{
		map->map = ft_realloc(map->map,
			ft_strlen(map->map) + ft_strlen(map->firstline) + 1);
		if (!map->map)
			return (ENOMEM);
		ft_memmove(map->map + ft_strlen(map->map), map->firstline,
			ft_strlen(map->firstline) + 1);
		map->firstline = get_next_line(fd);
		if (errno)
			return (errno);
	}
	if (map->firstline)
	{
		free(map->firstline);
		map->firstline = NULL;
	}
	return (0);
}

/**
 * @brief entry point for matrix loading.
 * @param map	map struct
 * @param fd	map file fd.
 * @return int 0 on success, errno val on failure.
 */
int init_map_content(t_map_elements *map, int fd)
{
	int	ret;

	ret = 0;
	ret = read_map(map, fd);
	if (ret)
		return (-1);
}
