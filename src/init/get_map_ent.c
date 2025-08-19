/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_ent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:19:43 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/19 19:14:46 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char *skip_to_map(int fd)
{
	char *line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
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

static float get_cardinal_direction(char c)
{
	if (c == 'N')
		return (90.0f);
	else if (c == 'S')
		return (270.0f);
	else if (c == 'W')
		return (180.0f);
	return (0.0f);
}

static int parse_map_line(char *line, t_map_elements *map, int y)
{
	int	x;

	x = 0;
	while(line[x])
	{
		if (line[x] == 'N' || line[x] == 'S'
			|| line[x] == 'E' || line[x] == 'W')
		{
			map->player.tail.x = x;
			map->player.tail.y = y;
			map->player.theta = get_cardinal_direction(line[x]);
		}
		x++;
	}
	return (x);
}

/**
 * @brief gets the cols,rows and player from the matrix.
 *
 * @param map struct
 * @param fd file descriptor of the map file
 * @return int 0 on success,-1 on failure.
 */
int get_map_ent(t_map_elements *map, int fd)
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
