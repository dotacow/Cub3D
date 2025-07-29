/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzabillah <hamzabillah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:43:16 by hamzabillah       #+#    #+#             */
/*   Updated: 2025/07/25 22:19:12 by hamzabillah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char **dup_map(char **map, int rows, int cols)
{
    char **copy;
    int i;
    int j;

    copy = malloc(sizeof(char *) * (rows + 1));
    i = 0;
    j = 0;
    if (!copy)
        return (NULL);
    while(i < rows)
    {
        copy[i] = malloc(cols + 1);
        if (!copy[i])
            return (NULL);
        while(j < cols)
        {
            copy[i][j] = map[i][j];
            j++;
        }
        copy[i][cols] = '\0';
        i++;
    }
    copy[rows] = NULL;
    return (copy);
}

static int flood_fill(char **map, int x, int y, int rows, int cols)
{
    if (x < 0 || y < 0 || x >= cols || y >= rows)
        return (0);
    if (map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == ' ')
        return (1);
    map[y][x] = 'F';
    if (!flood_fill(map, x+1, y, rows, cols))
        return (0);
    if (!flood_fill(map, x-1, y, rows, cols))
        return (0);
    if (!flood_fill(map, x, y+1, rows, cols))
        return (0);
    if (!flood_fill(map, x, y-1, rows, cols))
        return (0);
    return (1);
} 
int validate_map_full(char **map)
{
    t_map_elements elem;
    char **map_copy;

    elem.map = map;
    elem.spawn_dir = '\0';
    elem.is_valid = false;
    if (!validate_map_content_struct(&elem) || !elem.is_valid)
        return (0);
    pad_map(map, elem.rows, elem.columns);
    if (!check_borders(map, elem.rows, elem.columns))
        return (0);
    map_copy = dup_map(map, elem.rows, elem.columns);
    if (!map_copy)
        return (0);
    if (!flood_fill(map_copy, elem.spawn_x, elem.spawn_y, elem.rows, elem.columns))
    {
        ft_putendl_fd("Error: Map is not closed (leak detected)", 2);
        free_split(map_copy);
        return (0);
    }
    free_split(map_copy);
    return (1);
}
