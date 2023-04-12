/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_i.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:22:19 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/12/20 23:32:00 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_i(int n)
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
		count += ft_print_i(n / 10);
		count += ft_print_i(n % 10);
	}
	else
		count += ft_print_c(n + '0');
	return (count);
}

// int main()
// {
// 	int i = ft_print_i(-2147483648);
// 	printf("\n%i\n", i);
// 	return (0);
// }