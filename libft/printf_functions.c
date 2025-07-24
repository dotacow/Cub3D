/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.amman>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 12:35:59 by hbelaih           #+#    #+#             */
/*   Updated: 2025/07/24 12:24:50 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *s)
{
	int	i;

	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = 0;
	while (*s)
	{
		ft_putchar((int)*s);
		i++;
		s++;
	}
	return (i);
}

int	printdigit(long n, int base)
{
	int			i;
	const char	*s;

	s = "0123456789abcdef";
	if (n < 0)
	{
		ft_putchar('-');
		return (printdigit(-n, base) + 1);
	}
	else if (n < (long)base)
		return (ft_putchar(s[n]));
	else
	{
		i = printdigit(n / base, base);
		return (i + printdigit(n % base, base));
	}
}

int	printdigit_upper(unsigned long n, int base)
{
	int			i;
	const char	*s;

	s = "0123456789ABCDEF";
	if (n < (unsigned long)base)
		return (ft_putchar(s[n]));
	else
	{
		i = printdigit_upper(n / base, base);
		return (i + printdigit_upper(n % base, base));
	}
}
