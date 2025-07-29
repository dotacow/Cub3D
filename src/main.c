/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzabillah <hamzabillah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:56:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/07/25 21:14:22 by hamzabillah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Written by Bruh

#include "../includes/cub3d.h"

#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.//
static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}


int32_t	main(int ac, char **av)
{
	int fd;

	// MLX allows you to define its core behaviour before startup.
	if (!validate_args(ac, av))
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	if (!is_valid_map(fd))
	{
		ft_putendl_fd("Error: Invalid map. Exiting.", 2);
		close(fd);
		return (1);
	}
	close(fd);
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "hello world ;p", false);
	if (!mlx)
		ft_error();

	/* Do stuff */
	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Even after the image is being displayed, we can still modify the buffer.
	mlx_put_pixel(img, 0, 0, 0xFF0000FF);

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}