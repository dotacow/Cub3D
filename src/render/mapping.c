/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:21:47 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/29 19:22:07 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void set_bounds(int *draw_start, int *draw_end, float line_height, int rows)
{
	*draw_start = -line_height / 2.0f + rows / 2.0f;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = line_height / 2.0f + rows / 2.0f;
	if (*draw_end >= rows)
		*draw_end = rows - 1;
}

static mlx_texture_t *get_tex(t_game *game, t_ray ray)
{
	if (!ray.side)
	{
		if (ray.step.x < 0)
			return (game->map.west);
		else
			return (game->map.east);
	}
	else
	{
		if (ray.step.y < 0)
			return (game->map.north);
		else
			return (game->map.south);
	}
}

static void put_rgb(t_game *game, int x, int draw_start, int draw_end)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		mlx_put_pixel(game->mlx.img, x, y, game->map.ceiling);
		y++;
	}
	y = draw_end;
	while (y < game->map.rows)
	{
		mlx_put_pixel(game->mlx.img, x, y, game->map.floor);
		y++;
	}
}

static void	put_tex(t_game *game, int draw_start, int draw_end,
						mlx_texture_t *tex, t_ray ray)
{
	int		y;
	int		tex_x;
	int		tex_y;
	float	wall_x;
	float	step;
	float	tex_pos;


	if (ray.side == 0)
		wall_x = ray.pos.y + ray.perp_dist * ray.dir.y;
	else
		wall_x = ray.pos.x + ray.perp_dist * ray.dir.x;
	wall_x -= floorf(wall_x);
	tex_x = (int)(wall_x * (float)tex->width);
	if ((ray.side == 0 && ray.dir.x > 0) || (ray.side == 1 && ray.dir.y < 0))
		tex_x = tex->width - tex_x - 1;
	step = 1.0f * tex->height / (draw_end - draw_start);
	tex_pos = 0.0f;
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		mlx_put_pixel(game->mlx.img, ray.pos.x, y,
			*(unsigned int *)(tex->pixels + (tex_y * tex->width + tex_x) * sizeof(unsigned int)));
		tex_pos += step;
		y++;
	}
}

void	map_ray(t_game *game, t_ray ray, int x)
{
	float			line_height;
	int				draw_start;
	int				draw_end;
	mlx_texture_t	*tex;

	line_height = game->map.rows / ray.perp_dist;
	if (!line_height)
		return ;
	set_bounds(&draw_start, &draw_end, line_height, game->map.rows);
	put_rgb(game, x, draw_start, draw_end);
	tex = get_tex(game, ray);
	if (!tex)
		return ;
	put_tex(game, draw_start, draw_end, tex, ray);
}
