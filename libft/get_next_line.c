/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:50:37 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/22 19:24:32 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}

static char	*ft_free(char *str)
{
	if (str)
		free(str);
	str = NULL;
	return (NULL);
}

static char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

static char	*fill_stash(int fd, char *buffer, char *stash)
{
	int	byte;

	while (!ft_strchr(stash, '\n'))
	{
		byte = read(fd, buffer, BUFFER_SIZE);
		if (byte == -1)
			return (ft_free(stash));
		if (byte == 0)
			break ;
		buffer[byte] = '\0';
		stash = ft_strjoin2(stash, buffer);
		if (!stash)
			return (ft_free(buffer));
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash[1024];
	char		*line;
	int			nlindex;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_calloc(1, 1);
	stash[fd] = fill_stash(fd, buffer, stash[fd]);
	free(buffer);
	if (!stash[fd] || *stash[fd] == '\0')
		return (ft_free(stash[fd]));
	nlindex = 0;
	while (stash[fd][nlindex] && stash[fd][nlindex] != '\n')
		nlindex++;
	line = ft_substr2(stash[fd], 0, nlindex);
	stash[fd] = ft_cutstash(stash[fd], nlindex + (stash[fd][nlindex] == '\n'));
	return (line);
}
