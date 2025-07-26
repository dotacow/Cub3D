/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:56:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/07/26 18:55:00 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	int	fd;
	// t_map_elements map;

	if (argc != 2 || !validate_args(argc, argv))
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	is_valid_map(fd);
	//map = init_map(fd);
	//cast_thy_rays(map);
	//loops_hooks and mlx stuff
	return (0);
}
