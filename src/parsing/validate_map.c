/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:28:55 by hbelaih           #+#    #+#             */
/*   Updated: 2025/07/25 00:37:39 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


/**
 * @brief this will read the map file line by line and validate each line
 *	according to each component's grammar
 * @param str
 * @param found
 * @return int
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

int is_map_content(char *line)
{
	if (!line || !*line)
		return (false);
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
 *  *   * validate xpm42
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
