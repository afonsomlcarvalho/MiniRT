/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:12:02 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/12/20 23:30:30 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	nl_index(char *stash)
{
	int	i;

	i = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

static char	*cleanup_crew(char **stash)
{
	char	*line;
	char	*temp;
	int		i;

	if (!*stash || **stash == '\0')
		return (NULL);
	i = nl_index(*stash);
	if (ft_strchr(*stash, '\n'))
	{
		line = ft_substr(*stash, 0, i + 1);
		temp = ft_substr(*stash, i + 1, ft_strlen(*stash) - i - 1);
		free(*stash);
		*stash = temp;
		if (**stash != '\0')
			return (line);
	}
	else
		line = ft_strdup(*stash);
	free(*stash);
	*stash = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	int			readchard;
	char		*buff;
	char		*temp;
	static char	*stash[OPEN_MAX];

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	readchard = read(fd, buff, BUFFER_SIZE);
	while (readchard > 0)
	{
		buff[readchard] = '\0';
		if (!stash[fd])
			stash[fd] = ft_strdup("");
		temp = ft_strjoin(stash[fd], buff);
		free(stash[fd]);
		stash[fd] = temp;
		if (ft_strchr(stash[fd], '\n'))
			break ;
		readchard = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	return (cleanup_crew(&stash[fd]));
}
