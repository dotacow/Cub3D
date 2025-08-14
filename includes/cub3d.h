/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:19:48 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/14 17:05:26 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// #include <cstddef>
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

/**
 * @brief enums for the frequency array used to help map validation
 * 
 */
typedef enum e_elements
{
	NO,
	SO,
	WE,
	EA,
	FLOOR,
	CEIL,
	PLAYER,
	MAP
}	t_elements;

/**
 * @brief a cartesian point in 2D space
 *
 */
typedef struct s_point
{
	float	x;
	float	y;
} t_point;

/** @note :I dont know if this is actually needed, we'll see.
 * @brief magnitude AND direction (⌐■_■)
 * @param tail: the point from which the vector starts
 * @param magnitude: the length of the vector
 * @param theta: angle measured counter-clockwise from the positive x-axis
 */
typedef struct s_vector
{
	t_point	tail;
	float	magnitude;
	float	theta;
} t_vector;

/**
 * @brief: contains the successfully validated map elements
 * @param map: flat matrix representing the map, p for padding, e for empty, w for wall.
 * @param north: north wall texture
 * @param south: south wall texture
 * @param west: west wall texture
 * @param east: east wall texture
 * @param floor: floor color (ARGB)
 * @param ceiling: ceiling color (ARGB)
 * @param columns: number of columns in the map (after padding, uniform across rows.)
 * @param rows: number of rows in the map (after padding, uniform across columns.)
 */
typedef struct s_map_elements
{
	unsigned int	floor;
	unsigned int	ceiling;
	char			*map;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	size_t			columns;
	size_t			rows;
} t_map_elements;

/**
 * @brief:the vector representing the camera pov
 * @param theta: the current direction of the camera, initialized (by hamooz) to N,S,W,E
 * @param position: the position
 */
typedef struct s_player
{
	float	theta;
	t_point	position;
} t_player;

void	check_name(char *name);
int		validate_args(int ac, char **av);
int		validate_map(const char *filename);
int		validate_map_grid(char **map);

#endif

