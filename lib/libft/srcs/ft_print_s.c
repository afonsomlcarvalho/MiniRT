/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:52:39 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/12/20 23:32:08 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_s(char *s)
{
	int	counter;

	counter = 0;
	if (!s)
	{
		counter = write(1, "(null)", 6);
		return (counter);
	}
	while (s[counter])
	{
		write(1, &s[counter], 1);
		counter++;
	}
	return (counter);
}

// int main()
// {
// 	char *str = "Print it\n";
// 	int i = ft_print_s(str);
// 	printf("%i\n", i);
// 	return 0;
// }