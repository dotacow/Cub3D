/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzabillah <hamzabillah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:03:06 by hbelaih           #+#    #+#             */
/*   Updated: 2025/09/04 11:57:12 by hamzabillah      ###   ########.fr       */
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
void	flood_fill(t_flood_ctx *ctx, int row, int col)
{
	char	cell;

	if (row < 0 || row >= ctx->rows || col < 0 || col >= ctx->cols)
		return ;
	cell = ctx->map[row][col];
	if (cell == '1' || cell == 'F')
		return ;
	if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W'
		|| cell == ' ')
	{
		ctx->map[row][col] = 'F';
		flood_fill(ctx, row - 1, col);
		flood_fill(ctx, row + 1, col);
		flood_fill(ctx, row, col - 1);
		flood_fill(ctx, row, col + 1);
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
int	find_player_position(t_flood_ctx *ctx)
{
	int	i;
	int	j;

	i = -1;
	ctx->player_row = -1;
	ctx->player_col = -1;
	while (++i < ctx->rows)
	{
		j = 0;
		while (j < ctx->cols)
		{
			if (ctx->map[i][j] == 'N' || ctx->map[i][j] == 'S'
				|| ctx->map[i][j] == 'E' || ctx->map[i][j] == 'W')
			{
				if (ctx->player_row != -1)
					return (0);
				ctx->player_row = i;
				ctx->player_col = j;
			}
			j++;
		}
	}
	if (ctx->player_row == -1)
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
	k = -1;
	while (++k < rows)
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
