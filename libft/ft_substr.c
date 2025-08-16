/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitane <yokitane@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 11:58:51 by yokitane          #+#    #+#             */
/*   Updated: 2025/08/16 15:30:47 by yokitane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len >= ft_strlen(s))
	{
		len = ft_strlen(s) - start;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = -1;
	while ((size_t)++i < len)
		str[i] = s[i + start];
	str[i] = '\0';
	return (str);
}
