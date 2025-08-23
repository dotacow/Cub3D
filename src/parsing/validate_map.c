/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:28:55 by hbelaih           #+#    #+#             */
/*   Updated: 2025/08/23 19:01:11 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief a wrapper to choose which validator to use based on the key
 * @param str the line to validate
 * @param found the frequency array to update and check from
 * @return int 1 if valid, 0 if not
 */
static int	validate_line(char *str, t_elements *found)
{
	char		**keyval;
	int			idx;
	int			ret;
	static int	(*validators[NMAPELEMENTS - 1])(char *,
			t_elements *found) = {validate_no, validate_so, validate_we,
		validate_ea, validate_floor, validate_ceil};

	if (!*str)
		return (true);
	keyval = ft_split(str, ' ');
	if (!keyval)
		return (false);
	idx = set_validator(keyval);
	if (idx != -1)
		ret = validators[idx](keyval[1], found);
	else
		ret = false;
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
		return (false);
	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (false);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
		{
			return (false);
		}
		i++;
	}
	return (true);
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

	valid = true;
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
		valid = false;
	if (line)
		free(line);
	line = NULL;
	return (valid && is_all_found(found));
}

/**
 * @brief evaluates the matrix section of the map file
 * @details ensures matrix is closed, and has a player spawn,
	and no invalid chars.
 * @warning TEMP IMPLEMENTATION TILL HAMZA FINISHES,
	ALWAYS RETURNS TRUE FOR NOW SO I CAN COMPILE MY CODE
 * @return true(1) if valid, false(0) if not.
 */
int	validate_map_content(char *line, t_elements *found, int fd)
{
	(void)line, (void)fd;
	found[MAP] = true;
	return (true);
}
