/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:10:46 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/11/01 12:34:30 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			sign;
	long long	result;

	sign = 1;
	result = 0;
	while ((*nptr == 32) || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == 45)
	{
		sign *= -1;
		nptr++;
	}
	else if (*nptr == 43)
		nptr++;
	while (*nptr >= 48 && *nptr <= 57)
	{
		result = result * 10;
		result += (sign * (*(nptr++) - '0'));
		if (result > 2147483647)
			return (-1);
		if (result < -2147483648)
			return (0);
	}
	return (result);
}
