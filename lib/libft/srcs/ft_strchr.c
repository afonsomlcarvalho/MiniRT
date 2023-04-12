/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:34:52 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/11/01 13:07:04 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	temp;

	temp = (unsigned char)c;
	while (temp != *s)
	{
		if (*s == 0)
			return (0);
		++s;
	}
	return ((char *)s);
}

// int main()
// {
// 	const char *str1 = "Test this string";
// 	printf("%p\n", ft_strchr(str1, '\0'));
// 	return (0);
// }