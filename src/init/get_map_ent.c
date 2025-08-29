/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_ent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:19:43 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/29 15:57:30 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*skip_to_map(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line || is_map_content(line))
		return (line);
	while (line && !is_map_content(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line && is_map_content(line))
		return (line);
	if (line)
	{
		free(line);
		line = NULL;
	}
	return (line);
}

/**
 * @brief translates char of player in matrix to radian.
 * @note if the way I parse the matrix (reversed y signage) causes problems,
 * I can probably just mirror Y angles here.
 * @param c
 * @return float
 */
static float	get_cardinal_direction(char c)
{
	if (c == 'N')
		return (FPI / 2.0f);
	else if (c == 'S')
		return (FPI * 1.5f);
	else if (c == 'W')
		return (FPI);
	return (0.0f);
}

static int	parse_map_line(char *line, t_map_elements *map, int y)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E'
			|| line[x] == 'W')
		{
			map->player.tail.x = x + 0.5f;
			map->player.tail.y = y + 0.5f;
			map->player.theta = get_cardinal_direction(line[x]);
			map->player.head = get_head(&map->player, 1.0f);
		}
		x++;
	}
	map->plane.tail.x = map->player.tail.x;
	map->plane.tail.y = map->player.tail.y;
	map->plane.theta = map->player.theta + (FPI / 2.0f);
	map->plane.head = get_head(&map->plane, 0.66f);
	return (x);
}

/**
 * @brief gets the cols,rows and player from the matrix.
 *
 * @param map struct
 * @param fd file descriptor of the map file
 * @return int 0 on success,-1 on failure.
 */
int	get_map_ent(t_map_elements *map, int fd)
{
	char	*line;
	int		x;
	int		y;

	line = skip_to_map(fd);
	if (!line)
		return (-1);
	y = 0;
	while (line && is_map_content(line))
	{
		x = parse_map_line(line, map, y);
		if (x > map->cols)
			map->cols = x;
		y++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
	{
		free(line);
		line = NULL;
	}
	map->rows = y;
	return (0);
}
