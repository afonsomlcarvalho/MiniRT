/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:24:05 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/12/20 23:31:52 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_d(int n)
{
	int				count;

	count = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		n *= -1;
		count += ft_print_c('-');
	}
	if (n >= 10)
	{
		count += ft_print_d(n / 10);
		count += ft_print_d(n % 10);
	}
	else
		count += ft_print_c(n + '0');
	return (count);
}
