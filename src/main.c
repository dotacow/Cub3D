/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:56:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/22 19:16:08 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	int	fd;
	t_map_elements map;

	if (!validate_args(argc, argv))
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	if(!is_valid_map(fd))
	{
		close(fd);
		ft_putendl_fd("Error\nmap misconfiguration!", 2);
		return (1);
	}
	close(fd);
	init_map(argv[1], &map);
	// if (!errno)
	//{
	//	cast_thy_rays(map);
	//...loops_hooks and mlx stuff...
	//}
	dump_map(&map);
	clean_map(&map);
	return (errno);
}
