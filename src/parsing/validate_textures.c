/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:07:34 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/24 17:26:49 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	set_validator(char **keyval)
{
	if (!keyval[0] || !keyval[1] || keyval[2])
		return (-1);
	if (!ft_strncmp(keyval[0], "NO", 3))
		return (NO);
	else if (!ft_strncmp(keyval[0], "SO", 3))
		return (SO);
	else if (!ft_strncmp(keyval[0], "WE", 3))
		return (WE);
	else if (!ft_strncmp(keyval[0], "EA", 3))
		return (EA);
	else if (!ft_strncmp(keyval[0], "F", 2))
		return (FLOOR);
	else if (!ft_strncmp(keyval[0], "C", 2))
		return (CEIL);
	return (-1);
}

int	validate_no(char *val, t_elements *found)
{
	mlx_texture_t	*texture;

	if (found[NO])
		return (false);
	found[NO] = true;
	texture = mlx_load_png(val);
	if (!texture)
		return (false);
	mlx_delete_texture(texture);
	return (true);
}

int	validate_so(char *val, t_elements *found)
{
	mlx_texture_t	*texture;

	if (found[SO])
		return (false);
	found[SO] = true;
	texture = mlx_load_png(val);
	if (!texture)
		return (false);
	mlx_delete_texture(texture);
	return (true);
}

int	validate_we(char *val, t_elements *found)
{
	mlx_texture_t	*texture;

	if (found[WE])
		return (false);
	found[WE] = true;
	texture = mlx_load_png(val);
	if (!texture)
		return (false);
	mlx_delete_texture(texture);
	return (true);
}

int	validate_ea(char *val, t_elements *found)
{
	mlx_texture_t	*texture;

	if (found[EA])
		return (false);
	found[EA] = true;
	texture = mlx_load_png(val);
	if (!texture)
		return (false);
	mlx_delete_texture(texture);
	return (true);
}
