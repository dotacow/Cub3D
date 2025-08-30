/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:21:47 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/30 14:56:27 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// static void set_bounds(int *draw_start, int *draw_end, float line_height, int rows)
// {
// 	*draw_start = -line_height / 2.0f + rows / 2.0f;
// 	if (*draw_start < 0)
// 		*draw_start = 0;
// 	*draw_end = line_height / 2.0f + rows / 2.0f;
// 	if (*draw_end >= rows)
// 		*draw_end = rows - 1;
// }

// static mlx_texture_t *get_tex(t_game *game, t_ray ray)
// {
// 	if (!ray.side)
// 	{
// 		if (ray.step.x < 0)
// 			return (game->map.west);
// 		else
// 			return (game->map.east);
// 	}
// 	else
// 	{
// 		if (ray.step.y < 0)
// 			return (game->map.north);
// 		else
// 			return (game->map.south);
// 	}
// }

// static void put_rgb(t_game *game, int x, int draw_start, int draw_end)
// {
// 	int	y;

// 	y = 0;
// 	while (y < draw_start)
// 	{
// 		mlx_put_pixel(game->mlx.img, x, y, game->map.ceiling);
// 		y++;
// 	}
// 	y = draw_end;
// 	while ((unsigned int)y < game->mlx.img->height)
// 	{
// 		mlx_put_pixel(game->mlx.img, x, y, game->map.floor);
// 		y++;
// 	}
// }

// static void	put_tex(t_game *game, int x, int draw_start, int draw_end,
// 						mlx_texture_t *tex, t_ray ray,float line_height)
// {
// 	int		y;
// 	unsigned int		tex_x;
// 	unsigned int		tex_y;
// 	float				wall_x;
// 	float				step;
// 	float				tex_pos;

// 	if (ray.side == 0)
// 		wall_x = ray.pos.y + ray.perp_dist * ray.dir.y;
// 	else
// 		wall_x = ray.pos.x + ray.perp_dist * ray.dir.x;
// 	wall_x -= floorf(wall_x);
// 	tex_x = (int)(wall_x * (float)tex->width);
// 	if ((ray.side == 0 && ray.dir.x > 0) || (ray.side == 1 && ray.dir.y < 0))
// 		tex_x = tex->width - tex_x - 1;
// 	step = (float)tex->height / (float)(draw_end - draw_start);
// 	tex_pos = (draw_start - game->mlx.img->height / 2.0f + line_height / 2.0f) * step;
// 	y = draw_start;
// 	while (y < draw_end)
// 	{
// 		tex_y = (int)tex_pos;
// 		if (tex_y >= tex->height)
// 			tex_y = tex->height - 1;
// 		unsigned int color = *(unsigned int *)(tex->pixels + ((tex_y * tex->width + tex_x) * sizeof(unsigned int)));
// 		mlx_put_pixel(game->mlx.img, x, y, color); // use screen column x
// 		tex_pos += step;
// 		y++;
// 	}
// }



int	get_draw_end(float line_height, int height)
{
	long	draw_end;

	draw_end = line_height / 2.0f + height / 2.0f;
	if (draw_end >= height)
		draw_end = height - 1;
	return ((int)draw_end);
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

static void	draw_ceiling(t_game *game, int col, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		mlx_put_pixel(game->mlx.img, col, y,game->map.ceiling);
		y++;
	}
}

static void	draw_floor(t_game *game, int col, int draw_end)
{
	int	y;

	y = draw_end;
	while (y < (int)game->mlx.img->height)
	{
		mlx_put_pixel(game->mlx.img, col, y,game->map.floor);
		y++;
	}
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_wall(t_game *game, int *col_and_draw_end, mlx_texture_t *texture,
		t_ray ray)
{
	int		y;
	int		d;
	int		tex_xy[2];
	int		idx;
	float	line_height;

	line_height = (float)game->mlx.img->height / ray.perp_dist;
	tex_xy[0] = get_tex_x(game, ray, texture);
	y = get_draw_start(line_height, game->mlx.img->height) - 1;
	while (++y <= col_and_draw_end[1])
	{
		d = y * 256 - game->mlx.img->height * 128 + (int)(line_height * 128);
		if( line_height == 0 )
			return ;
		tex_xy[1] = ((d * texture->height) / (int)line_height) / 256;
		if (tex_xy[0] >= 0 && tex_xy[0] < (int)texture->width && tex_xy[1] >= 0
			&& tex_xy[1] < (int)texture->height)
		{
			idx = (tex_xy[1] * texture->width + tex_xy[0]) * 4;
			mlx_put_pixel(game->mlx.img, col_and_draw_end[0], y,
				get_rgba(texture->pixels[idx + 0], texture->pixels[idx + 1],
					texture->pixels[idx + 2], texture->pixels[idx + 3]));
		}
	}
}

mlx_texture_t	*get_wall_texture(t_game *game, t_ray ray)
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
	// float			line_height;
	// int				draw_start;
	// int				draw_end;
	// mlx_texture_t	*tex;

	// line_height = (float)game->mlx.img->height / ray.perp_dist;
	// if (!line_height)
	// 	return ;
	// set_bounds(&draw_start, &draw_end, line_height, game->mlx.img->height);
	// put_rgb(game, x, draw_start, draw_end);
	// tex = get_tex(game, ray);
	// if (!tex)
	// 	return ;
	// put_tex(game, x, draw_start, draw_end, tex, ray, line_height);
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
	if (line_height == 0)
		return ;
	draw_start = get_draw_start(line_height, game->mlx.img->height);
	draw_end = get_draw_end(line_height, game->mlx.img->height);
	texture = get_wall_texture(game, ray);
	if (!texture)
		return ;
	draw_ceiling(game, x, draw_start);
	draw_wall(game, (int []){x, draw_end}, texture, ray);
	draw_floor(game, x, draw_end);
}
