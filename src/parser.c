#include "../inc/minirt.h"

void	parsing_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	exit(0);
}

void	parser(int argc, char **argv)
{
	int		fd;
	char	*line;
	char	**info;

	if (argc != 2)
		parsing_error("Invalid number of arguments.\n");
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		info = ft_split(line, ' ');
		if (!ft_strncmp("C", info[0], ft_strlen(info[0])))
			setup_camera(info);
		else if (!ft_strncmp("sp", info[0], ft_strlen(info[0])))
			add_sphere(info);
		else if (!ft_strncmp("A", info[0], ft_strlen(info[0])) || !ft_strncmp("L", info[0], ft_strlen(info[0])))
			light_setup(info, info[0][0] == 'L');
		else if (!ft_strncmp("pl", info[0], ft_strlen(info[0])))
			add_plane(info);
		free_array(info);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
