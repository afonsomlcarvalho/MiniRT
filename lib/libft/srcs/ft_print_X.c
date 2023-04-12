/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_X.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:45:21 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/12/20 23:32:56 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ux(unsigned int num)
{
	int		counter;
	char	*base;

	counter = 0;
	base = "0123456789ABCDEF";
	if (num >= 16)
		counter += ft_print_ux(num / 16);
	counter += write(1, &base[num % 16], 1);
	return (counter);
}
