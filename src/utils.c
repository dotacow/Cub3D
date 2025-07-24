/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:29:11 by hbelaih           #+#    #+#             */
/*   Updated: 2025/07/24 16:30:19 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

void	check_name(char *name)
{
	char	*cub;
	int		i;
	int		j;

	if (ft_strlen(name) < 4)
	{
		perror("Error\nmap must name .cub\n");
		exit(1);
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
			perror("Error\nmap must be name .cub\n");
			exit(1);
		}
	}
}

int validate_args(int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		errno = EINVAL;
		perror("Error\nCub3d");
		ft_putendl_fd("Usage: ./cub3d <map.cub>", STDERR_FILENO);
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		errno = EACCES;
		perror("Error\nCub3D"); 
		return (0);
	}
	close(fd);
	check_name(av[1]);
	return (1);
}
