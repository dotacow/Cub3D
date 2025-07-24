/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   found_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:15:52 by yokitane          #+#    #+#             */
/*   Updated: 2025/07/24 20:16:55 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief inits the map elements to not yet found (0)
 * usage: found[NO|SO...|MAP] = 1 on found
 * @param found the frequency array to check for previously found elements
 */
void init_found_arr(t_elements *found)
{
	int i;

	i = -1;
	while(++i < NMAPELEMENTS)
		found[i] = false;
}

int is_all_found(t_elements *found)
{
	int	i;

	i = -1;
	while(++i < NMAPELEMENTS)
		if (found[i] == false)
			return (false);
	return (true);
}
