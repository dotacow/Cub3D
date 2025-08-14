/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:28:55 by hbelaih           #+#    #+#             */
/*   Updated: 2025/08/14 17:11:25 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"
#include <asm-generic/errno-base.h>

/**
 * @brief inits the map elements to not yet found (-1)
 * usage: found[NO|SO...|MAP] = 0 on found
 * @param found the frequency array to check for previously found elements 
 */
static void init_found_arr(t_elements *found)
{
    int i;

    i = -1;
    while(++i < 8)
        found[i] = -1;
}

/**
 * @brief this will read the map file line by line and validate each line
 * exigencies: in line check if:
 *  * NO|SO|WE|EA
 *  *   * validate file permessions, validate file type(xpm).
 *  * F|C
 *  *   * validate each rgb value
 *  * 1|0
 *  *   * if not found all needed map elements, throw error
 *  *   * validate map contents
 *  * else
 *  *   * foreign character found, return error
 * @param filename 
 * @return int 
 */
/**
 * @brief finds the maximum width among all map rows
 * @param map the map as array of strings
 * @return the maximum width
 */
static int	find_max_width(char **map)
{
	int	max_width;
	int	current_width;
	int	i;

	max_width = 0;
	i = 0;
	while (map[i])
	{
		current_width = ft_strlen(map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

/**
 * @brief counts the number of rows in the map
 * @param map the map as array of strings
 * @return the number of rows
 */
static int	count_rows(char **map)
{
	int	rows;

	rows = 0;
	while (map[rows])
		rows++;
	return (rows);
}

/**
 * @brief creates a rectangular padded version of the map
 * @param map the original map
 * @param width the target width for padding
 * @param height the number of rows
 * @return the padded map or NULL on failure
 */
static char	**create_padded_map(char **map, int width, int height)
{
	char	**padded;
	int		i;
	int		j;
	int		len;

	padded = malloc(sizeof(char *) * (height + 1));
	if (!padded)
		return (NULL);
	i = 0;
	while (i < height)
	{
		padded[i] = malloc(sizeof(char) * (width + 1));
		if (!padded[i])
			return (NULL);
		len = ft_strlen(map[i]);
		j = 0;
		while (j < len)
		{
			padded[i][j] = map[i][j];
			j++;
		}
		while (j < width)
		{
			padded[i][j] = ' ';
			j++;
		}
		padded[i][width] = '\0';
		i++;
	}
	padded[height] = NULL;
	return (padded);
}

/**
 * @brief frees the padded map
 * @param padded the padded map to free
 * @param height the number of rows
 */
static void	free_padded_map(char **padded, int height)
{
	int	i;

	if (!padded)
		return ;
	i = 0;
	while (i < height)
	{
		free(padded[i]);
		i++;
	}
	free(padded);
}

/**
 * @brief checks if a character is a player start position
 * @param c the character to check
 * @return 1 if player, 0 otherwise
 */
static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/**
 * @brief checks if a tile is walkable (0 or player)
 * @param c the character to check
 * @return 1 if walkable, 0 otherwise
 */
static int	is_walkable(char c)
{
	return (c == '0' || is_player(c));
}

/**
 * @brief validates a single tile and its neighbors
 * @param padded the padded map
 * @param x the x coordinate
 * @param y the y coordinate
 * @param width the map width
 * @param height the map height
 * @return 1 if valid, 0 if invalid
 */
static int	validate_tile(char **padded, int x, int y, int width, int height)
{
	if (!is_walkable(padded[y][x]))
		return (1);
	if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
		return (0);
	if (padded[y - 1][x] == ' ' || padded[y + 1][x] == ' ' ||
		padded[y][x - 1] == ' ' || padded[y][x + 1] == ' ')
		return (0);
	return (1);
}

/**
 * @brief validates the map using neighbor-checking method
 * @param map the map as array of strings
 * @return 1 if valid, 0 if invalid
 */
int	validate_map_grid(char **map)
{
	char	**padded;
	int		width;
	int		height;
	int		x;
	int		y;

	if (!map || !map[0])
		return (0);
	width = find_max_width(map);
	height = count_rows(map);
	padded = create_padded_map(map, width, height);
	if (!padded)
		return (0);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (!validate_tile(padded, x, y, width, height))
			{
				free_padded_map(padded, height);
				return (0);
			}
			x++;
		}
		y++;
	}
	free_padded_map(padded, height);
	return (1);
}

/**
 * @brief checks if a line contains only map characters
 * @param line the line to check
 * @return 1 if map line, 0 otherwise
 */
static int	is_map_line(char *line)
{
	int	i;

	if (!line || !line[0])
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' &&
			line[i] != 'W' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief removes newline character from end of string
 * @param line the string to trim
 */
static void	trim_newline(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

/**
 * @brief reads and validates the map from file
 * @param filename the file to read
 * @return 1 if valid, 0 if invalid
 */
int validate_map(const char *filename)
{
    int fd;
    char *line;
    char **map_lines;
    int map_started;
    int line_count;
    int i;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        ft_putendl_fd("Error\nCannot open map file", STDERR_FILENO);
        return (0);
    }
    
    map_lines = malloc(sizeof(char *) * 1000); // Assume max 1000 lines
    if (!map_lines)
    {
        close(fd);
        return (0);
    }
    
    map_started = 0;
    line_count = 0;
    line = get_next_line(fd);
    
    while (line)
    {
        trim_newline(line);
        
        if (is_map_line(line))
        {
            map_started = 1;
            map_lines[line_count] = line;
            line_count++;
        }
        else if (map_started)
        {
            // Found non-map line after map started - invalid
            free(line);
            break;
        }
        else
        {
            // Still in header section, skip this line
            free(line);
        }
        
        line = get_next_line(fd);
    }
    
    close(fd);
    map_lines[line_count] = NULL;
    
    if (line_count == 0)
    {
        ft_putendl_fd("Error\nNo valid map found", STDERR_FILENO);
        free(map_lines);
        return (0);
    }
    
    // Validate the map grid
    if (!validate_map_grid(map_lines))
    {
        ft_putendl_fd("Error\nInvalid map", STDERR_FILENO);
        i = 0;
        while (i < line_count)
        {
            free(map_lines[i]);
            i++;
        }
        free(map_lines);
        return (0);
    }
    
    // Clean up
    i = 0;
    while (i < line_count)
    {
        free(map_lines[i]);
        i++;
    }
    free(map_lines);
    return (1);
}
