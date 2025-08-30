/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:10:11 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/30 13:43:19 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	dump_map(t_map_elements *map)
{
	int	i;

	if (!map || !map->map)
	{
		ft_putendl_fd("Map is NULL", 2);
		return ;
	}
	printf( "floor: 0x%.6X, ceiling: 0x%.6X\n", map->floor,
		map->ceiling);
	printf("Player and plane: pos(%.2f, %.2f), dir(%.2f, %.2f), plane(%.2f, %.2f)\n",
		map->player.pos.x, map->player.pos.y, map->player.dir.x,
		map->player.dir.y, map->player.plane.x, map->player.plane.y);
	printf( "Map (%i rows x %i cols):\n", map->rows, map->cols);
	i = 0;
	while (i < (int)(map->rows))
	{
		write(2, map->map + (i * (map->cols) ), map->cols);
		write(2, "\n", 1);
		i++;
	}
	ft_putchar_fd('\n', 2);
}
