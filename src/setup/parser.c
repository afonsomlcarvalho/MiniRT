/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:53 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 16:11:08 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	parsing_error(char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(str, 2);
	return (1);
}

static int	check_name(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	return ((filename[i - 3] != '.') + (filename[i - 2] != 'r') \
			+ (filename[i - 1] != 't'));
}

void	line_treatment(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (i)
		line[i] = 0;
}

void	parse_line(char *line, int *error)
{
	char	**info;

	line_treatment(line);
	info = ft_split(line, ' ');
	if (!info[0])
		return ;
	if (!ft_strncmp("C", info[0], ft_strlen(info[0])))
		*error += setup_camera(info);
	else if (!ft_strncmp("sp", info[0], ft_strlen(info[0])))
		*error += add_sphere(info);
	else if (!ft_strncmp("A", info[0], ft_strlen(info[0])) \
	|| !ft_strncmp("L", info[0], ft_strlen(info[0])))
		*error += light_setup(info, info[0][0] == 'L');
	else if (!ft_strncmp("pl", info[0], ft_strlen(info[0])))
		*error += add_plane(info);
	else if (!ft_strncmp("cy", info[0], ft_strlen(info[0])))
		*error += add_cylinder(info);
	else if (!ft_strncmp("co", info[0], ft_strlen(info[0])))
		*error += add_cone(info);
	else if (info[0][0] != '\n')
		*error += parsing_error("Invalid identifier.\n");
	free_array(info);
	free(line);
}

void	parser(int argc, char **argv)
{
	int			fd;
	char		*line;
	static int	error;

	g_scene.cam_counter = 0;
	if (argc != 2)
	{
		parsing_error("Invalid number of arguments.\n");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (check_name(argv[1]) || fd == -1)
		error += parsing_error("Invalid filename.\n");
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, &error);
		line = get_next_line(fd);
	}
	close(fd);
	verify_parse(&error);
	is_error(error);
}
