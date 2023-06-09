/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:06:29 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 16:11:37 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	error_handler(void)
{
	parsing_error("Dynamic memory allocation failed\n");
	free_all(1);
	exit(EXIT_FAILURE);
}

void	is_error(int error)
{
	if (error)
	{
		free_all(0);
		exit(EXIT_FAILURE);
	}
}
