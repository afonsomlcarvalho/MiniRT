/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:02:03 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/12/20 23:32:04 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hex(unsigned long int mem)
{
	int		counter;
	char	*base;

	base = "0123456789abcdef";
	counter = 0;
	if (mem >= 16)
		counter += ft_hex(mem / 16);
	counter += write(1, &base[mem % 16], 1);
	return (counter);
}

int	ft_print_p(unsigned long int mem)
{
	int	counter;

	counter = 0;
	if (!mem)
	{
		counter = write(1, "(nil)", 5);
		return (counter);
	}
	counter += write(1, "0x", 2) + ft_hex(mem);
	return (counter);
}
