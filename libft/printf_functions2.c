/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:35:21 by hbelaih           #+#    #+#             */
/*   Updated: 2025/07/24 12:24:20 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	hex_len(unsigned long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		len++;
		n /= 16;
	}
	return (len);
}

static void	print_hex(unsigned long num)
{
	const char	*s;

	s = "0123456789abcdef";
	if (num >= 16)
		print_hex(num / 16);
	ft_putchar(s[num % 16]);
}

int	print_pointer(unsigned long l)
{
	int				len;

	len = 0;
	if (l == 0)
	{
		len += write(1, "(nil)", 5);
		return (len);
	}
	else
		len += write(1, "0x", 2);
	print_hex(l);
	len += hex_len(l);
	return (len);
}
