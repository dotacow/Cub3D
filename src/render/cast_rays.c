/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:56:38 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/29 19:36:00 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	cast_ray(char *grid, t_ray *ray, int cols)
{
	while (!ray->hit)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (grid[(int)(ray->map.y * cols + ray->map.x)] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_dist = (ray->map.x - ray->pos.x + (1 - ray->step.x) / 2.0f) / ray->dir.x;
	else
		ray->perp_dist = (ray->map.y - ray->pos.y + (1 - ray->step.y) / 2.0f) / ray->dir.y;
}

static void render(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		ray = get_ray_ent(game, x);
		cast_ray(game->map.map, &ray, game->map.cols);
		map_ray(game, ray, x);
		x++;
	}
}

void	cast_thy_rays(void *game)
{
	hook_redirect(game);
	render((t_game *)game);
}