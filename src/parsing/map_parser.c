/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:28:55 by hbelaih           #+#    #+#             */
/*   Updated: 2025/09/11 13:31:24 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief a wrapper to choose which validator to use based on the key
 * @param str the line to validate
 * @param found the frequency array to update and check from
 * @return int 1 if valid, 0 if not
 */
int	validate_line(char *str, t_elements *found)
{
	char		**keyval;
	int			idx;
	int			ret;
	static int	(*validators[])(char *, t_elements *) = {validate_no,
		validate_so, validate_we, validate_ea, validate_floor, validate_ceil};

	if (!*str)
		return (1);
	keyval = ft_split(str, ' ');
	if (!keyval)
		return (0);
	idx = set_validator(keyval);
	if (idx != -1)
		ret = validators[idx](keyval[1], found);
	else
		ret = 0;
	free_split(keyval);
	return (ret);
}

/**
 * @brief are you in the matrix(content) part, or in the textures part?
 *
 * @param line the line to check
 * @return int 1 if the line is part of the map content, 0 if not
 */
int	is_map_content(char *line)
{
	int	i;

	if (!line || !*line || *line == '\n')
		return (0);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * @brief this will read the map file line by line and validate each line
 * @details: in line check if (after trim):
 *  * NO|SO|WE|EA
 *  *   * validate texture file.
 *  * F|C
 *  *   * validate each rgb value (0-255)
 *  * 1|0
 *  *   * validate map contents
 *  * else
 *  *   * foreign character found, return error
 * @param fd map file descriptor (not validated)
 * @return 1 if valid, 0 if not
 */
int	is_valid_map(int fd)
{
	char		*line;
	t_elements	found[NMAPELEMENTS];
	int			valid;

	valid = 1;
	init_found_arr(found);
	line = get_next_line(fd);
	while (line && !is_map_content(line) && valid)
	{
		trim_whitespace(line);
		valid = validate_line(line, found);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	if (valid && line)
		valid = validate_map_content(line, found, fd);
	else
		valid = 0;
	if (line)
		free(line);
	line = NULL;
	return (valid && is_all_found(found));
}

/**
 * @brief setup map data by reading lines and creating 2D copy
 * @param ctx context containing file descriptor and first line of map content
 * @param lines pointer to store array of lines
 * @param map_copy pointer to store 2D map copy
 * @return 1 on success, 0 on failure
 */
int	setup_map_data(t_map_read_ctx *ctx, char ***lines, char ***map_copy)
{
	*lines = read_all_map_lines(ctx);
	if (!*lines)
		return (0);
	*map_copy = create_2d_map_copy(*lines, ctx->rows, ctx->cols);
	if (!*map_copy)
	{
		free_lines(*lines, ctx->rows);
		return (0);
	}
	return (1);
}

/**
 * @brief evaluates the matrix section of the map file
 * @details ensures matrix is closed, and has a player spawn,
	and no invalid chars.
 * Uses flood fill algorithm to validate map enclosure.
 * @param line first line of map content
 * @param found frequency array to mark MAP as found
 * @param fd file descriptor positioned at map content
 * @return true(1) if valid, false(0) if not.
 */
int	validate_map_content(char *line, t_elements *found, int fd)
{
	t_map_read_ctx	ctx;
	char			**lines;
	char			**map_copy;
	int				valid;

	if (!line || !*line)
		return (0);
	ctx.fd = fd;
	ctx.first_line = line;
	if (!setup_map_data(&ctx, &lines, &map_copy))
		return (0);
	if (has_invalid_map_char(lines))
	{
		free_lines(lines, ctx.rows);
		free_map_copy(map_copy, ctx.rows);
		return (0);
	}
	valid = process_map_validation(lines, map_copy, ctx.rows, ctx.cols);
	if (valid)
		found[MAP] = 1;
	return (valid);
}
