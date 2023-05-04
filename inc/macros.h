/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:10 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:05:11 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

# include "minirt.h"

# define X	0
# define Y	1
# define Z	2

# define WIDTH	1080
# define HEIGHT	1080
# define THREAD	40

# define DEF_SPEC		200
# define REFLECTIONS	2
# define BACKGROUND		0
# define RUGGED			0

// # define malloc(x) NULL

# define RED_TEXT 		"\033[0;31m"
# define GREEN_TEXT 	"\033[0;32m"
# define YELLOW_TEXT 	"\033[0;33m"
# define BLUE_TEXT 		"\033[0;34m"
# define PURPLE_TEXT	"\033[0;35m"
# define CYAN_TEXT 		"\033[0;36m"
# define CYAN_BOLD 		"\033[1;36m"
# define RESET_TEXT 	"\033[0;0m"

#endif
