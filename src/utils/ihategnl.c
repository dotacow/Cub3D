/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ihategnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:20:53 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/23 16:34:57 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief this is to get rid of the still reachable memory leak from get_next_line
 * @note: not mandatory, but why not, will just remove if it causes issues.
 * @param fd1
 * @param fd2
 * @param fd3
 */
void	ihategnl(int fd1, int fd2, int fd3)
{
	char *l1;
	char *l2;
	char *l3;

	l1 = get_next_line(fd1);
	while (l1)
	{
		if (l1)
			free(l1);
		l1 = get_next_line(fd1);
	}
	l2 = get_next_line(fd2);
	while(l2)
	{
		if (l2)
			free(l2);
		l2 = get_next_line(fd2);
	}
	l3 = get_next_line(fd3);
	while (l3)
	{
		if (l3)
			free(l3);
		l3 = get_next_line(fd3);
	}
}
