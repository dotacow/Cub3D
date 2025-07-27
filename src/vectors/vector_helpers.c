/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:13:51 by yokitane          #+#    #+#             */
/*   Updated: 2025/07/27 21:15:05 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	bzero_point(t_point *p)
{
	if (!p)
		return;
	p->x = 0.0f;
	p->y = 0.0f;
}

void	bzero_vector(t_vector *v)
{
	if (!v)
		return;
	bzero_point(&v->tail);
	v->magnitude = 0.0f;
	v->theta = 0.0f;
}