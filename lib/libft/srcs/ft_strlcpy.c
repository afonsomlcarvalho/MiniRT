/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:00:18 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/10/24 16:19:18 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;	
	size_t	srcsize;

	if (!dst && !src)
		return (0);
	i = 0;
	srcsize = ft_strlen(src);
	if (size != 0)
	{
		while (src[i] && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}

// int main()
// {
// 	char dst[6];
// 	char *src = "Copy this up there.";
// 	int ret = ft_strlcpy(dst, src, 7);
// 	printf("%s, with return value %d\n", dst, ret);
// 	return (0);
// }