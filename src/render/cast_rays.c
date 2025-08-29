/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:56:38 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/29 17:24:49 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void cast_ray(t_game *game);

static t_ray get_ray_ent(t_game *game, int x)
{
	t_ray	prime;
	float	cam_x;



	return (prime);
}
static void render(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		ray = get_ray_ent(game, x);
		
	}

}

void	cast_thy_rays(void *game)
{
	hook_redirect(game);
	render((t_game *)game);
}