/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:35:01 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/10/10 23:35:02 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*joined;

	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s1 || !s2 || !joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		joined[i] = s2[j];
		i++;
		j++;
	}
	joined[i] = '\0';
	return (joined);
}

// int main()
// {
// 	char *str1 = "Join ";
// 	char *str2 = "This";
// 	char *joined = ft_strjoin(str1, str2);
// 	printf("%s\n", joined);
// 	free(joined);
// 	return (0);
// }