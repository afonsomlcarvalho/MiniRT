#include "../inc/minirt.h"

int	parsing_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	return (1);
}

int	check_name(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	return ((filename[i - 3] != '.') + (filename[i - 2] != 'r') + (filename[i - 1] != 't'));
}

void	parser(int argc, char **argv)
{
	int			fd;
	char		*line;
	char		**info;
	static int	error;

	if (argc != 2)
		error += parsing_error("Invalid number of arguments.\n");
	fd = open(argv[1], O_RDONLY);
	if (check_name(argv[1]) || fd == -1)
		error += parsing_error("Invalid filename.\n");
	line = get_next_line(fd);
	while (line)
	{
		info = ft_split(line, ' ');
		if (!ft_strncmp("C", info[0], ft_strlen(info[0])))
			error += setup_camera(info);
		else if (!ft_strncmp("sp", info[0], ft_strlen(info[0])))
			error += add_sphere(info);
		else if (!ft_strncmp("A", info[0], ft_strlen(info[0])) || !ft_strncmp("L", info[0], ft_strlen(info[0])))
			error += light_setup(info, info[0][0] == 'L');
		else if (!ft_strncmp("pl", info[0], ft_strlen(info[0])))
			error += add_plane(info);
		else if (!ft_strncmp("cy", info[0], ft_strlen(info[0])))
			error += add_cyllinder(info);
		// else if (info[0][0] != '\n')
		// 	error += parsing_error("Invalid identifier.\n");
		free_array(info);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (error)
		free_all(0);
}
