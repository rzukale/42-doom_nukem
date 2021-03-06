/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:46:02 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/16 09:59:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_square(t_buffer *buffer, t_xy offset, int c, int s)
{
	int				x;
	int				y;
	t_pxl_coords	xy;

	x = 0;
	y = 0;
	while (y < s)
	{
		x = 0;
		while (x < s)
		{
			xy.x = x + offset.x;
			xy.y = y + offset.y;
			put_pixel(buffer, xy, c);
			x++;
		}
		y++;
	}
}
