/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:35:46 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/30 15:36:43 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

int	get_draw_end(float line_height, int height)
{
	int	draw_end;

	draw_end = line_height / 2.0f + height / 2.0f;
	if (draw_end >= height)
		draw_end = height - 1;
	return (draw_end);
}

int	get_draw_start(float line_height, int height)
{
	int	draw_start;

	draw_start = -line_height / 2.0f + height / 2.0f;
	if (draw_start < 0)
		draw_start = 0;
	return (draw_start);
}

int	get_tex_x(t_game *game, t_ray ray, mlx_texture_t *texture)
{
	float	wall_x;
	int		tex_x;

	if (ray.side == 0)
		wall_x = game->map.player.pos.y + ray.perp_dist * ray.dir.y;
	else
		wall_x = game->map.player.pos.x + ray.perp_dist * ray.dir.x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (float)texture->width);
	if ((ray.side == 0 && ray.dir.x > 0) || (ray.side == 1 && ray.dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}
