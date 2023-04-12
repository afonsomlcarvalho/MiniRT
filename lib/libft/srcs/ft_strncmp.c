/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:35:11 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/11/01 12:35:22 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i])
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

// int main()
// {
// 	const char str1[] = "";
// 	const char str2[] = "asd";
// 	size_t n = 4;
// 	printf("Mine: %i | Original: %i\n", ft_strncmp(str1, str2, n),
//	strncmp(str1, str2, n));
// 	return (0);
// }