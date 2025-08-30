/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray_ent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:34:01 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/30 15:05:35 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

static void	set_step(t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (ray->pos.x - ray->map.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - ray->pos.x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (ray->pos.y - ray->map.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - ray->pos.y) * ray->delta.y;
	}
}


t_ray	get_ray_ent(t_game *game, int x)
{
	t_ray	ray;
	float	cam_x;

	cam_x = 2.0f * (float)x / (float)game->mlx.img->width - 1.0f;
	ray.dir.x = game->map.player.dir.x + game->map.player.plane.x * cam_x;
	ray.dir.y = game->map.player.dir.y + game->map.player.plane.y * cam_x;
	ray.map.x = (int)game->map.player.pos.x;
	ray.map.y = (int)game->map.player.pos.y;
	if (ray.dir.x == 0)
		ray.delta.x = 1e30;
	else
		ray.delta.x = fabsf(1.0f / ray.dir.x);
	if (ray.dir.y == 0)
		ray.delta.y = 1e30;
	else
		ray.delta.y = fabsf(1.0f / ray.dir.y);
	ray.hit = 0;
	ray.side = -1;
	ray.perp_dist = 0.0;
	ray.pos = game->map.player.pos;
	set_step(&ray);
	return (ray);
}

