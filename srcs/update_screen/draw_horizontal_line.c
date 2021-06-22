/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_horizontal_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:56:39 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/22 10:36:17 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	draw_horizontal_line(Uint32 *buffer, float *depth_buffer,
	t_texel *tex, t_steps *step)
{
	t_uvz	texel;
	int		cur_x;
	float	offset;
	float	offset_step;

	offset = 0.0f;
	cur_x = step->start_x;
	texel = step->start_uv;
	offset_step = 1.0f / ((float)(step->end_x - step->start_x));
	if (step->start_x < 0 || step->cur_y > SCREEN_HEIGHT - 1
		|| step->cur_y < 0 || step->end_x > SCREEN_WIDTH - 1)
		return (FALSE);
	while (cur_x < step->end_x)
	{
		texel.u = (1.0f - offset) * step->start_uv.u + offset * step->end_uv.u;
		texel.v = (1.0f - offset) * step->start_uv.v + offset * step->end_uv.v;
		texel.w = (1.0f - offset) * step->start_uv.w + offset * step->end_uv.w;
		if (texel.w > depth_buffer[cur_x + step->cur_y * SCREEN_WIDTH])
		{
			texel = texel_inv_z(texel);
			put_pixel(buffer, cur_x, step->cur_y,
				get_texel(
					&(t_uv){texel.u * tex->width - 1, texel.v * tex->height - 1},
					&(t_uv){tex->width, tex->height}, tex->texels));
			depth_buffer[cur_x + step->cur_y * SCREEN_WIDTH] = texel.w;
		}
		offset += offset_step;
		cur_x++;
	}
	return (TRUE);
}
