/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 22:03:00 by hamzabillah       #+#    #+#             */
/*   Updated: 2025/07/12 13:30:06 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delimiter(char c, const char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;
	char		*token_start;

	if (str)
		last = str;
	if (!last || !*last)
		return (NULL);
	while (*last && is_delimiter(*last, delim))
		last++;
	if (!*last)
		return (NULL);
	token_start = last;
	while (*last && !is_delimiter(*last, delim))
		last++;
	if (*last)
	{
		*last = '\0';
		last++;
	}
	return (token_start);
}
