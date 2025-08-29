/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ray_ent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:34:01 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/29 17:53:26 by yokitane         ###   ########.fr       */
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
	t_ray	prime;
	float	cam_x;

	cam_x = 2.0f * (float)x / (float)WIDTH - 1.0f;
	prime.pos.x = game->map.player.tail.x;
	prime.pos.y = game->map.player.tail.y;
	prime.map.x = (int)prime.pos.x;
	prime.map.y = (int)prime.pos.y;
	prime.dir.x = (game->map.player.head.x - game->map.player.tail.x) +
		cam_x * game->map.plane.head.x;
	prime.dir.y = (game->map.player.head.y - game->map.player.tail.y) +
		cam_x * game->map.plane.head.y;
	if (prime.dir.x == 0)
		prime.delta.x = (float)INFINITY;
	else
		prime.delta.x = fabsf(1.0f / prime.dir.x);
	if (prime.dir.y == 0)
		prime.delta.y = (float)INFINITY;
	else
		prime.delta.y = fabsf(1.0f / prime.dir.y);
	set_step(&prime);
	prime.hit = 0;
	prime.side = -1;
	prime.perp_dist = 0.0f;
	return (prime);
}

