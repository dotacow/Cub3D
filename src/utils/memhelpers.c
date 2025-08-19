/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memhelpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:37:09 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/19 15:37:24 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void *ft_realloc(void *ptr, size_t new_size)
{
	void *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		ptr = NULL;
		return (ptr);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memmove(new_ptr, ptr, new_size);
	free(ptr);
	ptr = NULL;
	return (new_ptr);
}