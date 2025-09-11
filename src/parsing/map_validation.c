/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:03:06 by hbelaih           #+#    #+#             */
/*   Updated: 2025/09/11 15:01:03 by hbelaih          ###   ########.fr       */
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
static int	check_map_interior(char **temp_map, int rows, int cols, int *valid)
{
	char	c;
	int		i;
	int		j;

       i = -1;
       while (++i < rows && *valid)
       {
	       j = -1;
	       while (++j < cols && *valid)
	       {
		       c = temp_map[i][j];
		       if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		       {
			       if (i == 0 || temp_map[i - 1][j] == '\0' || temp_map[i - 1][j] == ' ')
				       *valid = 0;
			       if (i == rows - 1 || temp_map[i + 1][j] == '\0' || temp_map[i + 1][j] == ' ')
				       *valid = 0;
			       if (j == 0 || temp_map[i][j - 1] == '\0' || temp_map[i][j - 1] == ' ')
				       *valid = 0;
			       if (j == cols - 1 || temp_map[i][j + 1] == '\0' || temp_map[i][j + 1] == ' ')
				       *valid = 0;
		       }
	       }
       }
       return (*valid);
}

static int	validate_map_temp(char **map_copy, int rows, int cols,
		t_flood_ctx *ctx)
{
	char	**temp_map;
	int		valid;

	temp_map = create_temp_map(map_copy, rows, cols);
	if (!temp_map)
		return (0);
	ctx->map = temp_map;
	flood_fill(ctx, ctx->player_row, ctx->player_col);
	valid = check_boundary_breach(temp_map, rows, cols);
	if (valid)
		check_map_interior(temp_map, rows, cols, &valid);
	free_temp_map(temp_map, rows);
	return (valid);
}

int	validate_map_enclosure(char **map_copy, int rows, int cols)
{
	t_flood_ctx	ctx;

	ctx.map = map_copy;
	ctx.rows = rows;
	ctx.cols = cols;
	if (!find_player_position(&ctx))
		return (0);
	return (validate_map_temp(map_copy, rows, cols, &ctx));
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
