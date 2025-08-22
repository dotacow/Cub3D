/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 00:51:22 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/22 15:23:38 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int is_rgb_format(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ',')
			return (false);
		str++;
	}
	return (true);
}
void	free_split(char **split)
{
	int i;

	if (!split)
		return;
	i = 0;
	while (split[i])
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	free(split);
}

int validate_floor(char *val, t_elements *found)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (found[FLOOR] || (ft_count_words(val, ',') != 3)
			|| !is_rgb_format(val))
		return (false);
	found[FLOOR] = true;
	rgb = ft_split(val, ',');
	if (!rgb)
		return (false);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	return (true);
}

int validate_ceil(char *val, t_elements *found)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	if (found[CEIL] || (ft_count_words(val, ',') != 3)
			|| !is_rgb_format(val))
		return (false);
	found[CEIL] = true;
	rgb = ft_split(val, ',');
	if (!rgb)
		return (false);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (false);
	return (true);
}
