/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:56:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/30 15:08:27 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_and_init(char *path, t_map_elements *map)
{
	int	ret;
	int	fd1;
	int	fd2;
	int	fd3;

	bzero_map(map);
	ret = 0;
	fd1 = open(path, O_RDONLY);
	fd2 = open(path, O_RDONLY);
	fd3 = open(path, O_RDONLY);
	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
		ret = 1;
	ret = !is_valid_map(fd1);
	if (ret)
		ft_putendl_fd("Error\nmap misconfiguration!", 2);
	if (!ret)
		ret = init_map(fd2, fd3, map);
	close(fd1);
	close(fd2);
	close(fd3);
	return (ret);
}

/**
 * @brief cub3d entry point
 * @param argc
 * @param argv
 * @return int
 */
int	main(int argc, char **argv)
{
	t_game	game;

	errno = 0;
	if (!validate_args(argc, argv))
		return (1);
	errno = validate_and_init(argv[1],&game.map);
	dump_map(&game.map);
	game.mlx.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", false);
	game.mlx.img = mlx_new_image(game.mlx.mlx, WIDTH, HEIGHT);
	if (game.mlx.mlx && game.mlx.img)
	{
		mlx_image_to_window(game.mlx.mlx, game.mlx.img, 0, 0);
		mlx_loop_hook(game.mlx.mlx, cast_thy_rays, &game);
		mlx_loop(game.mlx.mlx);
	}
	clean_all(&game.map,&game.mlx);
	return (errno);
}
