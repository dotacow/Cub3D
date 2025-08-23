/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:03:06 by hbelaih           #+#    #+#             */
/*   Updated: 2025/08/23 17:15:57 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief flood fill algorithm to check if position leads to map boundary
 * @param map_copy 2D map array
 * @param x x coordinate
 * @param y y coordinate
 * @param rows number of rows
 * @param cols number of columns
 * @return int 1 if flood fill reaches boundary (invalid),
	0 if contained (valid)
 */
void	flood_fill(char **map, int row, int col, int total_rows, int total_cols)
{
	char	cell;

	if (row < 0 || row >= total_rows || col < 0 || col >= total_cols)
		return ;
	cell = map[row][col];
	if (cell == '1' || cell == 'F')
		return ;
	if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W'
		|| cell == ' ')
	{
		map[row][col] = 'F';
		flood_fill(map, row - 1, col, total_rows, total_cols);
		flood_fill(map, row + 1, col, total_rows, total_cols);
		flood_fill(map, row, col - 1, total_rows, total_cols);
		flood_fill(map, row, col + 1, total_rows, total_cols);
	}
}

/**
 * @brief find player position in the map
 * @param map 2D map array
 * @param rows number of rows
 * @param cols number of columns
 * @param player_row pointer to store player row
 * @param player_col pointer to store player column
 * @return 1 if exactly one player found, 0 otherwise
 */
int	find_player_position(char **map, int rows, int cols,
		int *player_row, int *player_col)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				if (*player_row != -1)
					return (0);
				*player_row = i;
				*player_col = j;
			}
			j++;
		}
		i++;
	}
	if (*player_row == -1)
		return (0);
	return (1);
}

/**
 * @brief free temporary map array
 * @param temp_map array to free
 * @param rows number of rows
 */
void	free_temp_map(char **temp_map, int rows)
{
	int	k;

	k = 0;
	while (k < rows)
	{
		free(temp_map[k]);
		k++;
	}
	free(temp_map);
}

/**
 * @brief create temporary map copy for flood fill
 * @param map_copy source map
 * @param rows number of rows
 * @param cols number of columns
 * @return temp map copy or NULL on failure
 */
char	**create_temp_map(char **map_copy, int rows, int cols)
{
	char	**temp_map;
	int		k;
	int		l;

	temp_map = (char **)malloc(sizeof(char *) * rows);
	if (!temp_map)
		return (NULL);
	k = 0;
	while (k < rows)
	{
		temp_map[k] = (char *)malloc(sizeof(char) * (cols + 1));
		if (!temp_map[k])
		{
			l = 0;
			while (l < k)
			{
				free(temp_map[l]);
				l++;
			}
			free(temp_map);
			return (NULL);
		}
		ft_strlcpy(temp_map[k], map_copy[k], cols + 1);
		k++;
	}
	return (temp_map);
}

/**
 * @brief check if flood fill reached map boundary
 * @param temp_map map after flood fill
 * @param rows number of rows
 * @param cols number of columns
 * @return 1 if no boundary breach, 0 if breach found
 */
int	check_boundary_breach(char **temp_map, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (temp_map[i][j] == 'F')
			{
				if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
