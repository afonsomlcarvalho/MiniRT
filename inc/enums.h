/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amorais- <amorais-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:08 by amorais-          #+#    #+#             */
/*   Updated: 2023/05/04 11:05:09 by amorais-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H

enum e_type
{
	SPHERE,
	CYLINDER,
	PLANE,
	CONE
};

enum e_reflection
{
	DIFFUSE,
	SPECULAR,
	BOTH
};

enum e_light
{
	AMBIENT,
	POINT
};

#endif
