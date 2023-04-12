/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:50:21 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/11/02 20:20:40 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

// int main()
// {
// 	t_list	*lst;
// 	t_list	*ls;
// 	t_list	*temp;
// 	int		i;

// 	i = 0;
// 	lst = ft_lstnew("Item 1");
// 	ls = lst;
// 	while (i < 3)
// 	{
// 		ls->next = ft_lstnew("Item-");
// 		ls = ls->next;
// 		i++;
// 	}
// 	ft_lstadd_front(&lst, ft_lstnew("New Item!"));
// 	ls = lst;
// 	while (ls)
// 	{
// 		printf("%s\n", ls->content);
// 		ls = ls->next;
// 	}
// 	while (lst)
// 	{
// 		temp = lst;
// 		lst = lst->next;
// 		free(temp);
// 	}
// 	return (0);
// }
