/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:34:49 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/11/02 15:03:19 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_counter(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	word_length(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*create_word(char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *)malloc(sizeof(char) * (word_length(s, c) + 1));
	if (!word)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**master;

	i = 0;
	master = (char **)malloc(sizeof(char *) * (word_counter(s, c) + 1));
	if (!master)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			master[i] = create_word(s, c);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	master[i] = NULL;
	return (master);
}

// int main(int argc, char **argv)
// {
// 	if (argc == 2)
// 	{
// 		char *str = argv[1];
// 		char **master = ft_split(str, ' ');

// 		for (int i = 0; i < word_counter(str, ' '); i++)
// 			printf("%s\n", master[i]);
// 		for (int i = 0; i < word_counter(str, ' '); i++)
// 			free(master[i]);
// 		free(master);
// 	}
// 	return (0);
// }