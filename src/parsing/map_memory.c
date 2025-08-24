/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:03:06 by hbelaih           #+#    #+#             */
/*   Updated: 2025/08/23 17:14:35 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief initialize map copy array with NULL pointers
 * @param map_copy array to initialize
 * @param rows number of rows
 */
void	init_map_copy(char **map_copy, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		map_copy[i] = NULL;
		i++;
	}
}

/**
 * @brief allocate memory for a single row
 * @param map_copy 2D array
 * @param row row index to allocate
 * @param cols number of columns
 * @return 1 on success, 0 on failure
 */
int	allocate_row(char **map_copy, int row, int cols)
{
	int	j;

	map_copy[row] = (char *)malloc(sizeof(char) * (cols + 1));
	if (!map_copy[row])
	{
		j = 0;
		while (j < row)
		{
			free(map_copy[j]);
			j++;
		}
		free(map_copy);
		return (0);
	}
	return (1);
}

/**
 * @brief fill a row with data from lines, padding with spaces
 * @param map_copy 2D map array
 * @param lines source lines array
 * @param row row index to fill
 * @param cols number of columns
 */
void	fill_row(char **map_copy, char **lines, int row, int cols)
{
	int	j;
	int	len;

	len = ft_strlen(lines[row]);
	if (len > 0 && lines[row][len - 1] == '\n')
		len--;
	j = 0;
	while (j < len && j < cols)
	{
		map_copy[row][j] = lines[row][j];
		j++;
	}
	while (j < cols)
	{
		map_copy[row][j] = ' ';
		j++;
	}
	map_copy[row][cols] = '\0';
}

/**
 * @brief creates a 2D map copy from the array of lines
 * @param lines array of map lines
 * @param rows number of rows
 * @param cols number of columns
 * @return char** 2D array copy of the map, NULL on failure
 */
char	**create_2d_map_copy(char **lines, int rows, int cols)
{
	char	**map_copy;
	int		i;

	map_copy = (char **)malloc(sizeof(char *) * rows);
	if (!map_copy)
		return (NULL);
	init_map_copy(map_copy, rows);
	i = 0;
	while (i < rows)
	{
		if (!allocate_row(map_copy, i, cols))
			return (NULL);
		fill_row(map_copy, lines, i, cols);
		i++;
	}
	return (map_copy);
}

/**
 * @brief free array of lines
 * @param lines array of strings to free
 * @param count number of lines
 */
void	free_lines(char **lines, int count)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < count)
	{
		if (lines[i])
			free(lines[i]);
		i++;
	}
	free(lines);
}
