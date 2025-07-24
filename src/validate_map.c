/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:28:55 by hbelaih           #+#    #+#             */
/*   Updated: 2025/07/24 17:18:24 by hbelaih          ###   ########.fr       */
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
int validate_map(const char *filename)
{
    int fd;
    char *line;
    t_elements found[8];
    
    if (fd < 0)
    {
        errno = EACCES;
        perror("Error opening file");
        exit(errno);
    }
    line = get_next_line(fd);
    while (line)
    {
        line = get_next_line(fd);
    }
}
