/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:28:55 by hbelaih           #+#    #+#             */
/*   Updated: 2025/07/24 20:17:44 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



static int validate_line(char *str,t_elements *found)
{
	char	**keyval;
	
	if (!*str)
		return (true);
}



/**
 * @brief this will read the map file line by line and validate each line
 * exigencies: in line check if (after trim):
 *  * NO|SO|WE|EA
 *  *   * validate file permessions, validate file type(xpm).
 *  * F|C
 *  *   * validate each rgb value (0-255)
 *  * 1|0
 *  *   * if not found all needed map elements, throw error
 *  *   * validate map contents
 *  * else
 *  *   * foreign character found, return error
 * @param fd map fd
 * @return 1 if valid, 0 if not
 */
int is_valid_map(int fd)
{
	char		*line;
	t_elements	found[NMAPELEMENTS];
	int			valid;

	valid = false;
	if (fd < 0)
	{
		errno = EACCES;
		perror("Error\nCub3D");
		exit(errno);
	}
	init_found_arr(found);
	line = get_next_line(fd);
	while (line)
	{
		trim_whitespace(line);
		valid = validate_line(line,found);
		free(line);
		if (!valid)
			break;
		line = get_next_line(fd);
	}
	return (valid && is_all_found(found));
}
