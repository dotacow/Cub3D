/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:36:22 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/29 19:34:08 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	clean_mlx(t_ftmlx *ftmlx)
{
	if (ftmlx)
	{
		if (ftmlx->mlx)
		{
			mlx_terminate(ftmlx->mlx);
			ftmlx->mlx = NULL;
		}
	}
	ftmlx = NULL;
}

void	clean_all(t_map_elements *map, t_ftmlx *ftmlx)
{
	clean_map(map);
	clean_mlx(ftmlx);
	exit(errno);
}