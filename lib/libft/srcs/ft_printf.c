/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gda-cruz <gda-cruz@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:30:58 by gda-cruz          #+#    #+#             */
/*   Updated: 2022/12/20 23:33:00 by gda-cruz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		counter;
	int		i;

	i = 0;
	counter = 0;
	va_start(ap, s);
	while (s[i])
	{
		if (s[i] == '%')
		{
			if (ft_strchr("cspdiuxX", s[++i]))
				counter += ((int (*)())ft_redirect(s[i]))(va_arg(ap, void *));
			else if (ft_strchr("+ #", s[i]) && ++i)
				counter += ((int (*)())ft_redirect_flags(s[i - 1], s[i]))
					(va_arg(ap, void *));
			else
				counter += write(1, &s[i], 1);
		}
		else
			counter += write(1, &s[i], 1);
		i++;
	}
	va_end(ap);
	return (counter);
}
