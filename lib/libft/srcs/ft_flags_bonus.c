/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:15:57 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/12/20 23:33:47 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_flag_plus(int n)
{
	int			count;

	count = 0;
	if (n >= 0)
		count += write(1, "+", 1);
	count += ft_print_i(n);
	return (count);
}

int	ft_flag_space(int n)
{
	int			count;

	count = 0;
	if (n >= 0)
		count += write(1, " ", 1);
	count += ft_print_i(n);
	return (count);
}

int	ft_flag_hash_l(unsigned int n)
{
	int			count;

	count = 0;
	if (n == 0)
	{
		count = write(1, "0", 1);
		return (count);
	}
	count += write(1, "0x", 2);
	count += ft_print_x(n);
	return (count);
}

int	ft_flag_hash_u(unsigned int n)
{
	int			count;

	count = 0;
	if (n == 0)
	{
		count = write(1, "0", 1);
		return (count);
	}
	count += write(1, "0X", 2);
	count += ft_print_ux(n);
	return (count);
}
