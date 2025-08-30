/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:19:48 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/30 14:16:12 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define NMAPELEMENTS 7
# define FPI 3.14159265359f
# define WIDTH 840
# define HEIGHT 640
# define FOV 0.66f
# define MS 0.05f
# define TURNRATE 0.05f
# define RIGHT 1.0f
# define LEFT -1.0f
# define FRWRD 1.0f
# define BKWRD -1.0f
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
}					t_elements;

/**
 * @brief a wrapper struct for mlx_t and all related stuff.
 * @note: will add members as needed.
 * @param mlx the mlx_t pointer
 */
typedef struct s_ftmlx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_ftmlx;

/**
 * @brief a cartesian point in 2D space
 *
 */
typedef struct s_point
{
	float			x;
	float			y;
}					t_point;


typedef struct s_player
{
	t_point pos;
	t_point dir;
	t_point plane;
}				t_player;
/**
 * @brief: contains the successfully validated map elements
 * @param map: flat matrix representing the map, 1 for wall, everything else empty
 * @param line: the first line of the map, used while loading map.
 * @param north: north wall texture
 * @param south: south wall texture
 * @param west: west wall texture
 * @param east: east wall texture
 * @param floor: floor color (ARGB)
 * @param ceiling: ceiling color (ARGB)
 * @param columns: number of columns in the map (after padding,
	uniform across rows.)
 * @param rows: number of rows in the map (after padding,
	uniform across columns.)
 * @param player: the player's position in the map
 * @param plane: the player's viewing plane (perpendicular to the direction of view)
 */
typedef struct s_map_elements
{
	int				rows;
	int				cols;
	unsigned int	floor;
	unsigned int	ceiling;
	char			*map;
	char			*line;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	t_player		player;
}					t_map_elements;

typedef struct s_ray
{
	t_point			dir;
	t_point			delta;
	t_point			pos;
	t_point			side_dist;
	t_point			map;
	t_point			step;
	double			perp_dist;
	int				hit;
	int				side;
}					t_ray;

typedef struct s_game
{
	t_map_elements	map;
	t_ftmlx			mlx;
}	t_game;

/*########## PARSING FUNCTIONS ##########*/
int					validate_args(int ac, char **av);
int					is_valid_map(int fd);
// map parser functions
int					validate_line(char *str, t_elements *found);
int					is_map_content(char *line);
int					setup_map_data(char *line, int fd, char ***lines,
						char ***map_copy, int *rows, int *cols);
int					validate_map_content(char *line, t_elements *found, int fd);
// map reader functions
int					process_line_length(char *line, int *max_cols);
void				init_lines_array(char **lines, int max_lines);
char				**read_remaining_lines(int fd, char **lines, int *count,
						int max_lines, int *max_cols);
char				**read_all_map_lines(int fd, char *first_line, int *rows,
						int *cols);
int					process_map_validation(char **lines, char **map_copy,
						int rows, int cols);
// map memory functions
void				init_map_copy(char **map_copy, int rows);
int					allocate_row(char **map_copy, int row, int cols);
void				fill_row(char **map_copy, char **lines, int row, int cols);
char				**create_2d_map_copy(char **lines, int rows, int cols);
void				free_lines(char **lines, int count);
// flood fill functions
void				flood_fill(char **map, int row, int col, int total_rows,
						int total_cols);
int					find_player_position(char **map, int rows, int cols,
						int *player_row, int *player_col);
void				free_temp_map(char **temp_map, int rows);
char				**create_temp_map(char **map_copy, int rows, int cols);
int					check_boundary_breach(char **temp_map, int rows, int cols);
// map validation functions
int					validate_map_enclosure(char **map_copy, int rows, int cols);
void				free_map_copy(char **map_copy, int rows);
// parsing utils
int					ft_isspace(char c);
void				trim_whitespace(char *str);
void				check_name(char *name);
int					is_rgb_format(char *str);
// frequency array utils
void				init_found_arr(t_elements *found);
int					is_all_found(t_elements *found);
// validators
int					set_validator(char **keyval);
int					validate_no(char *val, t_elements *found);
int					validate_so(char *val, t_elements *found);
int					validate_we(char *val, t_elements *found);
int					validate_ea(char *val, t_elements *found);
int					validate_floor(char *val, t_elements *found);
int					validate_ceil(char *val, t_elements *found);
/*########## GENERAL FUNCTIONS ##########*/
void				free_split(char **split);
char				*skip_to_map(int fd);
/*########## INIT FUNCTIONS ##########*/
void				bzero_map(t_map_elements *map);
int					init_map(int fd1, int fd2, t_map_elements *map);
int					init_map_elements(t_map_elements *map, int fd);
int					init_map_content(t_map_elements *map, int fd);
int					read_map(t_map_elements *map, int fd);
int					get_map_ent(t_map_elements *map, int fd);
/*########## LOADING FUNCTIONS ##########*/
int					load_data(t_map_elements *map, char *line);
void				bzero_point(t_point *p);
/*######## RAYCASTING FUNCTIONS ########*/
void				cast_thy_rays(void *game);
void				map_ray(t_game *game,t_ray ray, int x);
t_ray				get_ray_ent(t_game *game, int x);
/*######## HOOK FUNCTIONS ########*/
void				hook_redirect(void *game);
/*########### CLEANUP FUNCTIONS ##########*/
void				clean_map(t_map_elements *map);
void				clean_mlx(t_ftmlx *ftmlx);
void				clean_all(t_map_elements *map,t_ftmlx *ftmlx);
/*######### DEBUGGING FUNCTIONS ##########*/
void				dump_map(t_map_elements *map);
#endif
