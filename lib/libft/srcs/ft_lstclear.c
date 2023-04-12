/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 15:42:56 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/10/24 16:15:35 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ls;

	if (!*lst)
		return ;
	while (*lst)
	{
		ls = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = ls;
	}
	lst = NULL;
}
