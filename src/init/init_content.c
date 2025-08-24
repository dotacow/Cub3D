/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 23:05:46 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/24 17:19:04 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief right pads a string with @param pad_char a given n times.
 *
 * @param str the string to pad
 * @param n ntimes to insert the pad_char
 */
static void	right_pad(char *str, int n, char pad_char)
{
	int	i;

	if (n <= 0)
		return ;
	i = 0;
	while (i < n)
	{
		str[i] = pad_char;
		i++;
	}
}

/**

 * @brief reads the map content from the file descriptor and
 *		 stores it in the map struct
 *
 * @param map
 * @param fd
 * @return int
 */
int	read_map(t_map_elements *map, int fd)
{
	int	offset;
	int	line_len;

	map->map = ft_calloc((map->rows * map->cols) + 1, sizeof(char));
	if (!map->map)
		return (ENOMEM);
	offset = 0;
	while (map->line && offset < (map->rows * map->cols))
	{
		line_len = ft_strlcpy(map->map + offset, map->line, map->cols + 1);
		right_pad(map->map + offset + line_len, map->cols - line_len, ' ');
		offset += map->cols;
		free(map->line);
		map->line = get_next_line(fd);
		if (errno)
			return (errno);
	}
	if (map->line)
	{
		free(map->line);
		map->line = NULL;
	}
	map->map[offset] = '\0';
	return (0);
}

/**
 * @brief entry point for matrix loading.
 * @param map	map struct
 * @param fd	map file fd.
 * @return int 0 on success, errno val on failure.
 */
int	init_map_content(t_map_elements *map, int fd)
{
	int	ret;

	if (!map->line)
		return (ENOMEM);
	ret = 0;
	ret = read_map(map, fd);
	if (ret)
		return (-1);
	return (0);
}
