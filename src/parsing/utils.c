/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:29:11 by hbelaih           #+#    #+#             */
/*   Updated: 2025/08/19 15:32:08 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


int		ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

void	trim_whitespace(char *str)
{
	char	*start;
	char	*end;
	size_t	len;

	if (!str || !*str)
		return;
	start = str;
	while (*start && ft_isspace(*start))
		start++;
	if (!*start)
	{
		*str = '\0';
		return;
	}
	end = start + ft_strlen(start) - 1;
	while (end > start && ft_isspace(*end))
		end--;
	len = end - start + 1;
	ft_memmove(str, start, len);
	str[len] = '\0';
}

void	check_name(char *name)
{
	char	*cub;
	int		i;
	int		j;

	if (ft_strlen(name) < 4)
	{
		errno = EINVAL;
		perror("Error\ncub3d");
		exit(errno);
	}
	i = 0;
	j = 3;
	cub = ".cub";
	while (name[i])
		i++;
	while (j >= 0)
	{
		if (cub[j--] != name[--i])
		{
			errno = EINVAL;
			perror("Error\ncub3d");
			exit(errno);
		}
	}
}

int validate_args(int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		errno = EINVAL;
		perror("Error\ncub3d");
		ft_putendl_fd("Usage: ./cub3d <map.cub>", STDERR_FILENO);
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		errno = EACCES;
		perror("Error\ncub3d");
		return (0);
	}
	close(fd);
	check_name(av[1]);
	return (1);
}
