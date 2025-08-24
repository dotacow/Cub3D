/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:13:51 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/24 17:04:00 by yokitane         ###   ########.fr       */
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

/**
 * @brief Get the magnitude of a vector
 *
 * @param v
 * @return float magnitude
 */
float	get_mag(t_vector *v)
{
	if (!v)
		return (0.0f);
	return (sqrtf((v->tail.x * v->tail.x) + (v->tail.y * v->tail.y)));
}
/**
 * @brief applies a rotation matrix to a vector
 * @param v vector to rotate
 * @param angle angle in degrees to rotate by
 */
void	rotate_vector(t_vector *v, float angle)
{
	t_point prime;

	if (!v)
		return ;
	angle = angle * (FPI / 180.0f);
	prime.x = v->tail.x * cosf(angle) - v->tail.y * sinf(angle);
	prime.y = v->tail.x * sinf(angle) + v->tail.y * cosf(angle);
	v->tail.x = prime.x;
	v->tail.y = prime.y;
}
