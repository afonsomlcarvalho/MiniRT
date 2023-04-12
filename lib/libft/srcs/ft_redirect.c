/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:30:58 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/12/21 00:44:38 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	(*ft_redirect(char c))
{
	if (c == 'c')
		return (&ft_print_c);
	else if (c == 'i')
		return (&ft_print_i);
	else if (c == 'd')
		return (&ft_print_d);
	else if (c == 's')
		return (&ft_print_s);
	else if (c == 'p')
		return (&ft_print_p);
	else if (c == 'x')
		return (&ft_print_x);
	else if (c == 'X')
		return (&ft_print_ux);
	else if (c == 'u')
		return (&ft_print_u);
	return (NULL);
}

void	(*ft_redirect_flags(char c, char d))
{
	if (c == '+' && ft_strchr("id", d))
		return (&ft_flag_plus);
	else if (c == ' ' && ft_strchr("id", d))
		return (&ft_flag_space);
	else if (c == ' ' && ft_strchr("spxXuc", d))
		return (ft_redirect(d));
	else if (c == '#' && d == 'x')
		return (&ft_flag_hash_l);
	else if (c == '#' && d == 'X')
		return (&ft_flag_hash_u);
	return (NULL);
}
