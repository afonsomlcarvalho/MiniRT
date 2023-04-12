/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:27:50 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/10/24 16:19:12 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;	
	size_t	d;

	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	i = 0;
	d = ft_strlen(dst);
	while (src[i] && size - d - 1 > 0)
	{
		dst[d] = src[i];
		d++;
		i++;
	}
	dst[d] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}

// int main()
// {
// 	char dst[15] = "Copy ";
// 	char *src = "this up there";
// 	int	ret = ft_strlcat(dst, src, 15);
// 	printf("%s, %d\n", dst, ret);
// 	return (0);
// }