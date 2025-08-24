/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:03:06 by hbelaih           #+#    #+#             */
/*   Updated: 2025/08/23 17:14:36 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief validate that all accessible areas are properly enclosed by walls
 * @param map_copy 2D map array
 * @param rows number of rows
 * @param cols number of columns
 * @return int 1 if valid (enclosed), 0 if invalid (not enclosed)
 */
int	validate_map_enclosure(char **map_copy, int rows, int cols)
{
	int		player_row;
	int		player_col;
	char	**temp_map;
	int		valid;

	player_row = -1;
	player_col = -1;
	if (!find_player_position(map_copy, rows, cols, &player_row, &player_col))
		return (0);
	temp_map = create_temp_map(map_copy, rows, cols);
	if (!temp_map)
		return (0);
	flood_fill(temp_map, player_row, player_col, rows, cols);
	valid = check_boundary_breach(temp_map, rows, cols);
	free_temp_map(temp_map, rows);
	return (valid);
}

/**
 * @brief free the 2D map copy
 * @param map_copy 2D array to free
 * @param rows number of rows
 */
void	free_map_copy(char **map_copy, int rows)
{
	int	i;

	if (!map_copy)
		return ;
	i = 0;
	while (i < rows)
	{
		if (map_copy[i])
			free(map_copy[i]);
		i++;
	}
	free(map_copy);
}
