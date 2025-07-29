/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzabillah <hamzabillah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 21:49:16 by hamzabillah       #+#    #+#             */
/*   Updated: 2025/07/25 22:19:15 by hamzabillah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || ft_strchr("NSEW", c));
}

static bool	process_map_row(char *row, t_map_elements *elem, int current_row)
{
	int	i;

	i = 0;
	while (row[i] && row[i] != '\n')
	{
		if (!is_valid_map_char(row[i]))
			return (false);
		if (ft_strchr("NSEW", row[i]))
		{
			elem->spawn_x = i;
			elem->spawn_y = current_row;
			elem->spawn_dir = row[i];
		}
		i++;
	}
	if (i > (int)elem->columns)
		elem->columns = i;
	return (true);
}

bool validate_map_content_struct(t_map_elements *elem)
{
	int	spawn_count;
	int	i;

	spawn_count = 0;
	i = 0;
	elem->columns = 0;
	while (elem->map[i])
	{
		if (!process_map_row(elem->map[i], elem, i))
			return (elem->is_valid = false);
		if (elem->spawn_dir != '\0')
			spawn_count++;
		i++;
	}
	elem->rows = i;
	if (spawn_count != 1)
		return (elem->is_valid = false);
	return (elem->is_valid = true);
}

// int check_characters_and_spawn(char **map, int *spawn_x, int *spawn_y, char *spawn_dir, int *rows, int *cols)
// {
//     int i = 0, j, spawn_count = 0, len;
//     while (map[i])
//     {
//         len = ft_strlen(map[i]);
//         if (len > *cols)
//             *cols = len;
//         j = 0;
//         while (map[i][j] && map[i][j] != '\n')
//         {
//             if (!is_allowed_char(map[i][j]))
//             {
//                 ft_putendl_fd("Error: Invalid character in map", 2);
//                 return (0);
//             }
//             if (ft_strchr("NSEW", map[i][j]))
//             {
//                 spawn_count++;
//                 *spawn_x = j;
//                 *spawn_y = i;
//                 *spawn_dir = map[i][j];
//             }
//             j++;
//         }
//         i++;
//     }
//     *rows = i;
//     if (spawn_count != 1)
//     {
//         ft_putendl_fd("Error: There must be exactly one spawn point (N/S/E/W)", 2);
//         return (0);
//     }
//     return (1);
// }

void pad_map(char **map, int rows, int cols)
{
    int i, len, j;
    char *new_line;
    for (i = 0; i < rows; i++)
    {
        len = ft_strlen(map[i]);
        if (len < cols)
        {
            new_line = malloc(cols + 1);
            if (!new_line)
                exit(1);
            for (j = 0; j < len; j++)
                new_line[j] = map[i][j];
            while (j < cols)
                new_line[j++] = ' ';
            new_line[cols] = '\0';
            free(map[i]);
            map[i] = new_line;
        }
    }
}

static int check_horizontal_borders(char **map, int rows, int cols)
{
    int j;

    j = 0;
    while (j < cols)
    {
        if (map[0][j] != '1' && map[0][j] != ' ')
        {
            ft_putendl_fd("Error: Top border not closed", 2);
            return (0);
        }
        if (rows > 1 && map[rows-1][j] != '1' && map[rows-1][j] != ' ')
        {
            ft_putendl_fd("Error: Bottom border not closed", 2);
            return (0);
        }
        j++;
    }
    return (1);
}

static int check_vertical_borders(char **map, int rows, int cols)
{
    int i;

    i = 0;
    while (i < rows)
    {
        if (map[i][0] != '1' && map[i][0] != ' ')
        {
            ft_putendl_fd("Error: Left border not closed", 2);
            return (0);
        }
        if (cols > 1 && map[i][cols-1] != '1' && map[i][cols-1] != ' ')
        {
            ft_putendl_fd("Error: Right border not closed", 2);
            return (0);
        }
        i++;
    }
    return (1);
}

int check_borders(char **map, int rows, int cols)
{
    if (!check_horizontal_borders(map, rows, cols))
        return (0);
    if (!check_vertical_borders(map, rows, cols))
        return (0);
    return (1);
}

// int check_borders(char **map, int rows, int cols)
// {
//     int i;
//     int j;

//     j = 0;
//     while (j < cols)
//     {
//         if (map[0][j] != '1' && map[0][j] != ' ')
//         {
//             ft_putendl_fd("Error: Top border not closed", 2);
//             return (0);
//         }
//         if (map[rows - 1][j] != '1' && map[rows - 1][j] != ' ')
//         {
//             ft_putendl_fd("Error: Bottom border not closed", 2);
//             return (0);
//         }
//         j++;
//     }
//     i = 0;
//     while (i < rows)
//     {
//         if (map[i][0] != '1' && map[i][0] != ' ')
//         {
//             ft_putendl_fd("Error: Left border not closed", 2);
//             return (0);
//         }
//         if (map[i][cols - 1] != '1' && map[i][cols - 1] != ' ')
//         {
//             ft_putendl_fd("Error: Right border not closed", 2);
//             return (0);
//         }
//         i++;
//     }
//     return (1);
// }

