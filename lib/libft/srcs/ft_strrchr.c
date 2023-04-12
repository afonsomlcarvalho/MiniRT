/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:41:37 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/11/04 16:29:06 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (unsigned char)c)
			return (&((char *)str)[i]);
		i--;
	}
	return (NULL);
}

// int main()
// {
// 	const char *str1 = "";
// 	printf("%p, %p\n", ft_strrchr(str1, '\0'), strrchr(str1, '\0'));
// 	return (0);
// }