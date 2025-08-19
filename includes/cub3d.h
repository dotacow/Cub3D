/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:19:48 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/19 19:23:33 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define NMAPELEMENTS 7

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
 * @param map: flat matrix representing the map, 0 for empty, 1 for wall, spaces are treated as 1's.
 * @param line: the first line of the map, used while loading map.
 * @param north: north wall texture
 * @param south: south wall texture
 * @param west: west wall texture
 * @param east: east wall texture
 * @param floor: floor color (ARGB)
 * @param ceiling: ceiling color (ARGB)
 * @param columns: number of columns in the map (after padding, uniform across rows.)
 * @param rows: number of rows in the map (after padding, uniform across columns.)
 * @param player: the player's position in the map
 * @param plane: the player's viewing plane (perpendicular to the direction of view)
 */
typedef struct s_map_elements
{
	unsigned int	floor;
	unsigned int	ceiling;
	char			*map;
	char			*line;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	int				cols;
	int				rows;
	t_vector		player;
	t_vector		plane;
} t_map_elements;

/*########## PARSING FUNCTIONS ##########*/
int				validate_args(int ac, char **av);
int				is_valid_map(int fd);
//parsing utils
int				ft_isspace(char c);
void			trim_whitespace(char *str);
void			check_name(char *name);
int				is_map_content(char *line);
int				is_rgb_format(char *str);
// frequency array utils
void			init_found_arr(t_elements *found);
int				is_all_found(t_elements *found);
//validators
int				set_validator(char **keyval);
int				validate_no(char *val, t_elements *found);
int				validate_so(char *val, t_elements *found);
int				validate_we(char *val, t_elements *found);
int				validate_ea(char *val, t_elements *found);
int				validate_floor(char *val, t_elements *found);
int				validate_ceil(char *val, t_elements *found);
int				validate_map_content(char *line, t_elements *found, int fd);
/*########## GENERAL FUNCTIONS ##########*/
void			free_split(char **split);
char			*skip_to_map(int fd);
/*########## INIT FUNCTIONS ##########*/
void		bzero_map(t_map_elements *map);
int			init_map(const char *path, t_map_elements *map);
int			init_map_elements(t_map_elements *map, int fd);
int			init_map_content(t_map_elements *map, int fd);
int			read_map(t_map_elements *map, int fd);
int			get_map_ent(t_map_elements *map, int fd);
/*########## LOADING FUNCTIONS ##########*/
int			load_data(t_map_elements *map, char *line);
/*########## MATH FUNCTIONS ##########*/
void			bzero_vector(t_vector *v);
void			bzero_point(t_point *p);
/*########## CLEANUP FUNCTIONS ##########*/
void			clean_map(t_map_elements *map);
#endif

