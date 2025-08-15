/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 23:05:46 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/15 23:19:12 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int init_map_content(t_map_elements *map, int fd)
{
	char	*line;

	line = map->firstline;
	while (line && is_map_content(line))
	{

	}
}
