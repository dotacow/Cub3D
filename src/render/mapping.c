/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:21:47 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/30 15:37:49 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	while ((unsigned int)y < game->mlx.img->height)
	{
		mlx_put_pixel(game->mlx.img, x, y, game->map.floor);
		y++;
	}
}


static void	calculate_wall_params(void *params[2], t_ray ray, int arr[2], float farr[2])
{
	t_game			*game;
	mlx_texture_t	*tex;
	float			wall_height;

	game = (t_game *)params[0];
	tex = (mlx_texture_t *)params[1];
	wall_height = (float)game->mlx.img->height / ray.perp_dist;
	farr[1] = (float)tex->height / wall_height;
	arr[0] = (int)(-wall_height / 2.0f + game->mlx.img->height / 2.0f);
	if (arr[0] < 0)
		arr[0] = 0;
	arr[1] = (int)(wall_height / 2.0f + game->mlx.img->height / 2.0f);
	if (arr[1] >= (int)game->mlx.img->height)
		arr[1] = game->mlx.img->height - 1;
	farr[0] = (arr[0] - game->mlx.img->height / 2.0f + wall_height / 2.0f)
		* farr[1];
}

static void	draw_wall(t_game *game, int screen_x, mlx_texture_t *tex, t_ray ray)
{
	int		arr[2];
	float	farr[2];
	int		idx;
	int		tex_y;
	void	*params[2];

	params[0] = game;
	params[1] = tex;
	calculate_wall_params(params, ray, arr, farr);
	while (arr[0] <= arr[1])
	{
		tex_y = (int)farr[0];
		if (tex_y >= (int)tex->height)
			tex_y = (int)tex->height - 1;
		idx = (tex_y * tex->width + get_tex_x(game, ray, tex)) * 4;
		mlx_put_pixel(game->mlx.img, screen_x, arr[0],
			get_rgba(tex->pixels[idx + 0], tex->pixels[idx + 1],
				tex->pixels[idx + 2], tex->pixels[idx + 3]));
		farr[0] += farr[1];
		arr[0]++;
	}
}

static mlx_texture_t	*get_wall_texture(t_game *game, t_ray ray)
{
	if (ray.side == 0)
	{
		if (ray.step.x > 0)
			return (game->map.east);
		else
			return (game->map.west);
	}
	else
	{
		if (ray.step.y > 0)
			return (game->map.south);
		else
			return (game->map.north);
	}
}


void	map_ray(t_game *game, t_ray ray, int x)
{
	float			line_height;
	int				draw_end;
	mlx_texture_t	*texture;
	int				draw_start;

	if (ray.side == 0)
		ray.perp_dist = (ray.map.x - game->map.player.pos.x + (1 - ray.step.x) / 2)
			/ ray.dir.x;
	else
		ray.perp_dist = (ray.map.y - game->map.player.pos.y + (1 - ray.step.y) / 2)
			/ ray.dir.y;
	line_height = (float)game->mlx.img->height / ray.perp_dist;
	draw_start = get_draw_start(line_height, game->mlx.img->height);
	draw_end = get_draw_end(line_height, game->mlx.img->height);
	texture = get_wall_texture(game, ray);
	if (!texture)
		return ;
	put_rgb(game, x, draw_start, draw_end);
	draw_wall(game, x,texture, ray);
}
