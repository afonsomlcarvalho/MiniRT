/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:35:22 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/11/01 13:36:10 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	l;

	if (!s)
		return (NULL);
	l = ft_strlen(s);
	if (start >= l)
	{
		sub = malloc(sizeof(char));
		if (!sub)
			return (NULL);
		*sub = '\0';
		return (sub);
	}
	if (l < len)
		return (ft_strdup((char *)s + start));
	i = 0;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (start < l && i < len)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

// int main()
// {
// 	char *str = "Sub this for me please";
// 	char *sub = ft_substr(str, 0, 30);
// 	printf("%s\n", sub);
// 	free(sub);
// 	return (0);
// }