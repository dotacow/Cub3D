/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:48:01 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/30 13:40:15 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

static void	move(t_game *game, float speed)
{
	t_player p;
	float new_x;
	float new_y;

	p = game->map.player;
	new_x = p.pos.x + p.dir.x * speed;
	new_y = p.pos.y + p.dir.y * speed;
	if (game->map.map[(int)new_y * game->map.cols + (int)p.pos.x] != '1')
		game->map.player.pos.y = new_y;
	if (game->map.map[(int)p.pos.y * game->map.cols + (int)new_x] != '1')
		game->map.player.pos.x = new_x;
}


static void	strafe(t_game *game, float speed)
{
	t_player p;
	float new_x;
	float new_y;

	p = game->map.player;
	new_x = p.pos.x + p.plane.x * speed;
	new_y = p.pos.y + p.plane.y * speed;
	if (game->map.map[(int)new_y * game->map.cols + (int)p.pos.x] != '1')
		game->map.player.pos.y = new_y;
	if (game->map.map[(int)p.pos.y * game->map.cols + (int)new_x] != '1')
		game->map.player.pos.x = new_x;
}

static void	turn(t_game *game, float dir)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = game->map.player.dir.x;
	game->map.player.dir.x = game->map.player.dir.x * cosf(dir)
		- game->map.player.dir.y * sinf(dir);
	game->map.player.dir.y = old_dir_x * sinf(dir)
		+ game->map.player.dir.y * cosf(dir);
	old_plane_x = game->map.player.plane.x;
	game->map.player.plane.x = game->map.player.plane.x * cosf(dir)
		- game->map.player.plane.y * sinf(dir);
	game->map.player.plane.y = old_plane_x * sinf(dir)
		+ game->map.player.plane.y * cosf(dir);
}

void	hook_redirect(void *game)
{
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(((t_game *)game)->mlx.mlx);
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_W))
		move((t_game *)game,(FRWRD * MS));
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_S))
		move((t_game *)game,(BKWRD * MS));
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_A))
		strafe((t_game *)game,(LEFT * MS));
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_D))
		strafe((t_game *)game,(RIGHT * MS));
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_LEFT))
		turn((t_game *)game, (LEFT * TURNRATE));
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_RIGHT))
		turn((t_game *)game, (RIGHT * TURNRATE));
}
