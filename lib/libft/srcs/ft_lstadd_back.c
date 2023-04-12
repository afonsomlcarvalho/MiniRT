/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:44:35 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/10/24 16:15:18 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ls;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ls = ft_lstlast(*lst);
	ls->next = new;
}

// int main()
// {
// 	t_list	*lst;
// 	t_list	*ls;
// 	int		i;

// 	i = 1;
// 	lst = ft_lstnew("Item.");
// 	ls = lst;
// 	while (i < 4)
// 	{
// 		ls->next = ft_lstnew("Item-");
// 		ls = ls->next;
// 		i++;
// 	}
// 	ft_lstadd_back(&lst, ft_lstnew("Last Item!"));
// 	while (lst)
// 	{
// 		printf("%s\n", lst->content);
// 		lst = lst->next;
// 	}
// 	return (0);
// }