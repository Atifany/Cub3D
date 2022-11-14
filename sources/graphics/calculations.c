/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atifany <atifany@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 19:26:41 by hnickole          #+#    #+#             */
/*   Updated: 2022/11/15 01:41:59 by atifany          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../_headers/cub3d.h"

double	deg_to_rad(float a)
{
	return (a * M_PI / 180);
}

double	rad_to_deg(float a)
{
	return (a / M_PI * 180);
}

unsigned int	darker(int c, int d)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = c >> 16;
	g = c >> 8;
	b = c;
	if (r > d)
		r -= d;
	else
		r = 0;
	if (g > d)
		g -= d;
	else
		g = 0;
	if (b > d)
		b -= d;
	else
		b = 0;
	return ((r << 16) + (g << 8) + b);
}
