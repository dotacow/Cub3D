/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:07:33 by hbelaih           #+#    #+#             */
/*   Updated: 2024/09/09 13:06:56 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*h;

	h = *lst;
	if (!h)
		return ;
	while (h)
	{
		temp = h->next;
		(*del)(h->content);
		free(h);
		h = temp;
	}
	*lst = NULL;
}
