/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 21:32:21 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/22 19:06:02 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int load_texture(t_map_elements *map,char *key, char *val)
{
	if (!ft_strncmp(key, "NO", 3))
	{
		map->north = mlx_load_png(val);
		if (!map->north)
			return (ENOMEM);
	}
	if (!ft_strncmp(key, "SO", 3))
	{
		map->south = mlx_load_png(val);
		if (!map->south)
			return (ENOMEM);
	}
	if (!ft_strncmp(key, "WE", 3))
	{
		map->west = mlx_load_png(val);
		if (!map->west)
			return (ENOMEM);
	}
	if (!ft_strncmp(key, "EA", 3))
	{
		map->east = mlx_load_png(val);
		if (!map->east)
			return (ENOMEM);
	}
	return (0);
}

static int load_color(t_map_elements *map, char *key, char *val)
{
	char **rgb;
	unsigned int color;

	color = 0;
	rgb = ft_split(val, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
	{
		free_split(rgb);
		return (ENOMEM);
	}
	color = (ft_atoi(rgb[0]) << 16) | (ft_atoi(rgb[1]) << 8)
		| ft_atoi(rgb[2]);
	if (key[0] == 'F')
		map->floor = color;
	else
		map->ceiling = color;
	free_split(rgb);
	return (0);
}

int	load_data(t_map_elements *map, char *line)
{
	char **keyval;
	int ret;

	ret = 0;
	keyval = ft_split(line, ' ');
	if (!keyval || !keyval[0] || !keyval[1])
	{
		free_split(keyval);
		return (ENOMEM);
	}
	if (keyval[0][0] == 'F' || keyval[0][0] == 'C')
		ret = load_color(map, keyval[0], keyval[1]);
	else
		ret = load_texture(map, keyval[0], keyval[1]);
	free_split(keyval);
	return (ret);
}
