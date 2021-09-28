/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_lamp_to_ceiling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:11:05 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/22 11:47:41 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	initialize_lamp_to_ceiling(t_entity *entity, t_home *home)
{
	unsigned int	i;
	t_surface		*ceiling;
	t_xyz			isection;
	t_bool			state;

	i = 0;
	isection = vec3(0, 0, 0);
	entity->pos.y = -99.0f;
	entity->top.normal = (t_xyz){0.0f, -1.0f, 0.0f, 0.0f};
	entity->bot.normal = (t_xyz){0.0f, -1.0f, 0.0f, 0.0f};
	ceiling = home->sectors[entity->sector_idx]->ceiling;
	while (i < home->sectors[entity->sector_idx]->nb_of_ceil)
	{
		state = vec3_ray_triangle_intersect(&ceiling->tri, entity->pos,
				vec3(0.0f, 1.0f, 0.0f), &isection);
		if (state)
			break ;
		ceiling = ceiling->next;
		i++;
	}
	if (state)
	{
		entity->pos.y = isection.y;
		entity->dir = ceiling->tri.normal;
	}
}