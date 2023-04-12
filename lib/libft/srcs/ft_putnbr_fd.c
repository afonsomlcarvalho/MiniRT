/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 22:22:22 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/11/02 18:10:26 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (n < 0)
	{
		num = (unsigned int)(-1 * n);
		ft_putchar_fd('-', fd);
	}
	else
		num = (unsigned int)(n);
	if (num >= 10)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
	else
		ft_putchar_fd(num + '0', fd);
}

// int main(int argc, char **argv)
// {
// 	int	fd;
// 	if (argc == 2)
// 	{
// 		fd = open(argv[1], O_RDWR);
// 		ft_putnbr_fd(483, fd);
// 		close(fd);
// 	}
// 	return (0);
// }