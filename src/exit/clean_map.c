/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:29:51 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/16 17:42:23 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


static void clean_textures(t_map_elements *map)
{
	if (map->north)
	{
		mlx_delete_texture(map->north);
		map->north = NULL;
	}
	if (map->south)
	{
		mlx_delete_texture(map->south);
		map->south = NULL;
	}
	if (map->west)
	{
		mlx_delete_texture(map->west);
		map->west = NULL;
	}
	if (map->east)
	{
		mlx_delete_texture(map->east);
		map->east = NULL;
	}
}


void	clean_map(t_map_elements *map)
{
	if (map->map)
	{
		free(map->map);
		map->map = NULL;
	}
	if(map->line)
	{
		free(map->line);
		map->line = NULL;
	}
	clean_textures(map);
	bzero_map(map);
}
