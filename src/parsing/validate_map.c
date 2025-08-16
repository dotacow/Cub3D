/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:28:55 by hbelaih           #+#    #+#             */
/*   Updated: 2025/08/16 14:34:37 by yokitane         ###   ########.fr       */
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
	static int	(*validators[NMAPELEMENTS - 1])(char *, t_elements *found)
		= {validate_no,
		validate_so,
		validate_we,
		validate_ea,
		validate_floor,
		validate_ceil
	};
	int		ret;

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
	free(keyval);
	return (ret);
}

/**
 * @brief are you in the matrix(content) part, or in the textures part?
 *
 * @param line the line to check
 * @return int 1 if the line is part of the map content, 0 if not
 */
int is_map_content(char *line)
{
	char	*trimmed_line;

	if (!line || !*line)
		return (false);
	trimmed_line = ft_strtrim(line, " \t\n\r\v\f");
	if (!trimmed_line || !*trimmed_line)
	{
		free(trimmed_line);
		return (false);
	}
	free(trimmed_line);
	if (*line != '1' && *line != '0' && *line != ' '
		&& ft_strncmp(line, "N", 3) != 0
		&& ft_strncmp(line, "S", 3) != 0
		&& ft_strncmp(line, "E", 3) != 0
		&& ft_strncmp(line, "W", 3) != 0)
		return (false);
	return (true);
}

/**
 * @brief this will read the map file line by line and validate each line
 * exigencies: in line check if (after trim):
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

	valid = false;
	init_found_arr(found);
	line = get_next_line(fd);
	while (line)
	{
		if(is_map_content(line))
		{
			valid = validate_map_content(line, found, fd);
			break ;
		}
		trim_whitespace(line);
		valid = validate_line(line, found);
		free(line);
		if (!valid)
			break ;
		line = get_next_line(fd);
	}
	return (valid && is_all_found(found));
}
/**
 * @brief evaluates the matrix section of the map file
 * @details ensures matrix is closed, and has a player spawn, and no invalid chars.
 * @warning TEMP IMPLEMENTATION TILL HAMZA FINISHES, ALWAYS RETURNS TRUE FOR NOW SO I CAN COMPILE MY CODE
 * @return true(1) if valid, false(0) if not.
 */
int	validate_map_content(char *line, t_elements *found, int fd)
{
	(void)line,(void)found,(void)fd;
	return (true);
}
