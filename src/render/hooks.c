/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 19:22:44 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/30 13:04:13 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"



static void turn(t_game *game,float dir)
{
	float	old_dir_x;
	float	old_plane_x;

	dir *= TURNRATE;
	old_dir_x = game->map.player.head.x;
	old_plane_x = game->map.plane.head.x;
	game->map.player.head.x = game->map.player.head.x * cosf(dir)
		- game->map.player.head.y * sinf(dir);
	game->map.player.head.y = old_dir_x * sinf(dir)
		+ game->map.player.head.y * cosf(dir);
	game->map.plane.head.x = game->map.plane.head.x * cosf(dir)
		- game->map.plane.head.y * sinf(dir);
	game->map.plane.head.y = old_plane_x * sinf(dir)
		+ game->map.plane.head.y * cosf(dir);

}

void	hook_redirect(void *game)
{
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(((t_game *)game)->mlx.mlx);
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_W))
		move_fwd((t_game *)game);
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_S))
		move_bwd((t_game *)game);
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_A))
		move_l((t_game *)game);
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_D))
		move_r((t_game *)game);
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_LEFT))
		turn((t_game *)game, LEFT);
	if (mlx_is_key_down(((t_game *)game)->mlx.mlx, MLX_KEY_RIGHT))
		turn((t_game *)game, RIGHT);
}
