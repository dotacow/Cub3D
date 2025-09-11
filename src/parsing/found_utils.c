/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:15:52 by yokitane          #+#    #+#             */
/*   Updated: 2025/09/10 17:05:50 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief inits the map elements to not yet found (0)
 * usage: found[NO|SO...|MAP] = true on found
 * @param found the frequency array to check for previously found elements
 */
void	init_found_arr(t_elements *found)
{
	int	i;

	i = -1;
	while (++i < NMAPELEMENTS)
		found[i] = false;
}

int	is_all_found(t_elements *found)
{
	int	i;

	i = -1;
	while (++i < NMAPELEMENTS)
		if (found[i] == false)
			return (false);
	return (true);
}
/**
 * @brief Checks if a character is a valid map content character.
 * @param c The character to check.
 * @return 1 if the character is valid, 0 otherwise.
 */

int	is_map_char(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Checks the map for any invalid characters.
 * @param map The 2D array of map strings.
 * @return 1 if all characters are valid, 0 otherwise.
 */
int	has_invalid_map_char(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (!is_map_char(map[i]))
			return (1);
		i++;
	}
	return (0);
}
