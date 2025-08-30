/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 12:48:01 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/30 12:53:15 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

void	move_fwd(t_game *game)
{
	t_point prime;

	prime.x = game->map.player.tail.x + game->map.player.head.x * MS;
	prime.y = game->map.player.tail.y + game->map.player.head.y * MS;
	if (game->map.map[(int)(prime.y * game->map.cols + game->map.player.tail.x)] != '1')
		game->map.player.tail.y = prime.y;
	if (game->map.map[(int)(game->map.player.tail.y * game->map.cols + prime.x)] != '1')
		game->map.player.tail.x = prime.x;
}

void move_bwd(t_game *game)
{
	t_point prime;

	prime.x = game->map.player.tail.x - game->map.player.head.x * MS;
	prime.y = game->map.player.tail.y - game->map.player.head.y * MS;
	if (game->map.map[(int)(prime.y * game->map.cols + game->map.player.tail.x)] != '1')
		game->map.player.tail.y = prime.y;
	if (game->map.map[(int)(game->map.player.tail.y * game->map.cols + prime.x)] != '1')
		game->map.player.tail.x = prime.x;
}

void move_l(t_game *game)
{
	t_point prime;

	prime.x = game->map.player.tail.x - game->map.plane.head.x * MS;
	prime.y = game->map.player.tail.y - game->map.plane.head.y * MS;
	if (game->map.map[(int)(prime.y * game->map.cols + game->map.player.tail.x)] != '1')
		game->map.player.tail.y = prime.y;
	if (game->map.map[(int)(game->map.player.tail.y * game->map.cols + prime.x)] != '1')
		game->map.player.tail.x = prime.x;
}

void move_r(t_game *game)
{
	t_point prime;

	prime.x = game->map.player.tail.x + game->map.plane.head.x * MS;
	prime.y = game->map.player.tail.y + game->map.plane.head.y * MS;
	if (game->map.map[(int)(prime.y * game->map.cols + game->map.player.tail.x)] != '1')
		game->map.player.tail.y = prime.y;
	if (game->map.map[(int)(game->map.player.tail.y * game->map.cols + prime.x)] != '1')
		game->map.player.tail.x = prime.x;
}
