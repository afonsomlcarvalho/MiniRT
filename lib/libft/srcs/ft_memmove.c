/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:19:25 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/11/08 15:05:15 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*temp;

	if (!dest && !src)
		return (0);
	temp = dest;
	if (src < dest)
	{
		dest += (n - 1);
		src += (n - 1);
		while (n--)
			*(char *)dest-- = *(char *)src--;
	}
	else if (src >= dest)
	{
		while (n--)
			*(char *)dest++ = *(char *)src++;
	}
	return (temp);
}
