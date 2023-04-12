/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:34:37 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/10/24 16:14:59 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_size(int num)
{
	int	size;

	size = 0;
	if (num >= 0 && num < 10)
		return (1);
	if (num < 0)
	{
		num *= -1;
		size++;
	}
	while (num > 0)
	{
		num /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		size;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	size = num_size(n);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	size--;
	if (n < 0)
	{
		result[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		result[size] = (n % 10) + '0';
		n /= 10;
		size--;
	}
	return (result);
}
