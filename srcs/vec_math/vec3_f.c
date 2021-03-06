/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 19:43:27 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/03 16:09:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	get_distance_squared(t_xyz pt0, t_xyz pt1)
{
	return (((pt1.x - pt0.x) * (pt1.x - pt0.x)
			+ (pt1.y - pt0.y) * (pt1.y - pt0.y)
			+ (pt1.z - pt0.z) * (pt1.z - pt0.z)));
}

t_xyz	vec3_calc_vector_average(t_raster_queue	*queue)
{
	int		i;
	t_xyz	average;

	i = queue->front;
	average = (t_xyz){0.0f, 0.0f, 0.0f, 0.0f};
	if (queue->size == 0)
		return ((t_xyz){0.0f, 0.0f, 0.0f, 0.0f});
	while (i < queue->rear)
	{
		average = vec3_add(average, queue->array[i].normal);
		i++;
	}
	average = vec3_unit_vector(average);
	return (average);
}

t_uvz	texel_mul(t_uvz *texel, float mul)
{
	t_uvz	new_texel;

	new_texel.u = texel->u * mul;
	new_texel.v = texel->v * mul;
	new_texel.w = texel->w * mul;
	return (new_texel);
}

t_uvz	texel_add(t_uvz *a, t_uvz *b)
{
	t_uvz	new_texel;

	new_texel.u = a->u + b->u;
	new_texel.v = a->v + b->v;
	new_texel.w = a->w + b->w;
	return (new_texel);
}

t_uvz	texel_lerp(t_uvz *texel_start, float steps, t_uvz *delta)
{
	t_uvz	new_texel;

	new_texel.u = texel_start->u + steps * delta->u;
	new_texel.v = texel_start->v + steps * delta->v;
	new_texel.w = texel_start->w + steps * delta->w;
	return (new_texel);
}
