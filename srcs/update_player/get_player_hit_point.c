/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_hit_point.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 13:38:50 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 12:35:51 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

float	get_player_hit_point(t_ray *ray, t_bullet_hole *hole, int bullet_sector)
{
	float		distance;
	t_plane		plr_plane;
	t_xyz		isection;

	distance = 400000000.0f;
	plr_plane = (t_plane){ray->plr_pos, vec3_unit_vector(vec3_dec(ray->pos,
				ray->plr_pos))};
	if (bullet_sector == ray->end_sector)
	{
		isection = vec3_intersection_with_ray_and_plane(&plr_plane,
				ray->pos, ray->dir);
		distance = get_distance_squared(ray->plr_pos, isection);
		if (distance <= 1.0f)
		{
			hole->type = player;
			hole->sector_idx = bullet_sector;
		}
	}
	return (distance);
}
