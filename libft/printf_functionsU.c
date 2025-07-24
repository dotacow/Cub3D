/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_functionsU.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:35:40 by hbelaih           #+#    #+#             */
/*   Updated: 2025/07/24 12:24:23 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_unsigned(unsigned int n)
{
	if (n >= 10)
		put_unsigned(n / 10);
	ft_putchar((n % 10) + '0');
}

static int	unsigned_len(unsigned int num)
{
	int	n;

	n = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		n++;
		num /= 10;
	}
	return (n);
}

int	print_unsigned(unsigned int num)
{
	put_unsigned(num);
	return (unsigned_len(num));
}
