/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:48:57 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/12/20 23:32:13 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_u(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_print_u(n / 10);
		count += ft_print_u(n % 10);
	}
	else
		count += ft_print_c(n + '0');
	return (count);
}
