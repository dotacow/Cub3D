/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:10:11 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/23 17:27:19 by yokitane         ###   ########.fr       */
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
	fprintf(stderr, "floor: 0x%.6X, ceiling: 0x%.6X\n", map->floor,
		map->ceiling);
	fprintf(stderr, "Player pos: (%.2f, %.2f)\n", map->player.tail.x,
		map->player.tail.y);
	fprintf(stderr, "Player dir: magnitude=%.2f, theta= %f rad\n",
		map->player.magnitude, (map->player.theta * 180 / M_PI));
	fprintf(stderr, "Map (%i rows x %i cols):\n", map->rows, map->cols);
	i = 0;
	while (i < (int)(map->rows * map->cols))
	{
		if (i && !(i % (int)map->cols))
			ft_putchar_fd('\n', 2);
		ft_putchar_fd(map->map[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
}
