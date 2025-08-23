/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:03:06 by hbelaih           #+#    #+#             */
/*   Updated: 2025/08/23 17:14:34 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief process line length and update max columns
 * @param line line to process
 * @param max_cols pointer to maximum columns counter
 * @return length of processed line
 */
int	process_line_length(char *line, int *max_cols)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	if (len > *max_cols)
		*max_cols = len;
	return (len);
}

/**
 * @brief initialize lines array with NULL pointers
 * @param lines array to initialize
 * @param max_lines number of lines to initialize
 */
void	init_lines_array(char **lines, int max_lines)
{
	int	i;

	i = 0;
	while (i < max_lines)
	{
		lines[i] = NULL;
		i++;
	}
}

/**
 * @brief read remaining lines from file descriptor
 * @param fd file descriptor
 * @param lines array to store lines
 * @param count pointer to line counter
 * @param max_lines maximum number of lines
 * @param max_cols pointer to maximum columns counter
 * @return lines array
 */
char	**read_remaining_lines(int fd, char **lines, int *count,
		int max_lines, int *max_cols)
{
	char	*current_line;

	current_line = get_next_line(fd);
	while (current_line && *count < max_lines)
	{
		lines[*count] = current_line;
		process_line_length(lines[*count], max_cols);
		(*count)++;
		current_line = get_next_line(fd);
	}
	if (current_line)
		free(current_line);
	return (lines);
}

/**
 * @brief reads all map lines and stores them in a static array
 * @param fd file descriptor positioned at map content
 * @param first_line first line of map content
 * @param rows pointer to store number of rows
 * @param cols pointer to store number of columns
 * @return char** array of map lines, NULL on failure
 */
char	**read_all_map_lines(int fd, char *first_line, int *rows, int *cols)
{
	char	**lines;
	int		max_lines;
	int		count;
	int		max_cols;

	max_lines = 100;
	count = 0;
	max_cols = 0;
	lines = (char **)malloc(sizeof(char *) * max_lines);
	if (!lines)
		return (NULL);
	init_lines_array(lines, max_lines);
	lines[count] = ft_strdup(first_line);
	if (!lines[count])
	{
		free(lines);
		return (NULL);
	}
	process_line_length(lines[count], &max_cols);
	count++;
	read_remaining_lines(fd, lines, &count, max_lines, &max_cols);
	*rows = count;
	*cols = max_cols;
	return (lines);
}

/**
 * @brief process map validation by running enclosure check and cleanup
 * @param lines array of map lines
 * @param map_copy 2D map array copy
 * @param rows number of rows
 * @param cols number of columns
 * @return 1 if valid, 0 if invalid
 */
int	process_map_validation(char **lines, char **map_copy, int rows, int cols)
{
	int	valid;

	valid = validate_map_enclosure(map_copy, rows, cols);
	free_lines(lines, rows);
	free_map_copy(map_copy, rows);
	return (valid);
}
