/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bullet_hit_point.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 16:08:07 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 11:42:30 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	test_ray(t_triangle *tri, t_bullet_hole *hole_2, float *d,
		t_ray *ray)
{
	t_plane	plane;
	t_xyz	hole;
	float	distance;
	float	dot;

	plane = (t_plane){tri->p[0], tri->normal};
	hole = vec3_intersection_with_ray_and_plane(&plane, ray->pos, ray->dir);
	dot = vec3_dot_product(vec3_unit_vector(vec3_dec(hole, ray->pos)),
			ray->dir);
	if (dot > 0.0f && vec3_is_inside_triangle(tri, hole))
	{
		if (vec3_dot_product(plane.normal, vec3_dec(plane.point, ray->pos)) < 0)
		{
			distance = get_distance_squared(hole, ray->pos);
			if (distance < *d)
			{
				*d = distance;
				hole_2->point = hole;
				hole_2->normal = tri->normal;
				return (true);
			}
		}
	}
	return (false);
}

t_bullet_hole	loop_through_sector(t_home *home, t_ray *ray, int bullet_sector)
{
	float			d[4];
	t_bullet_hole	hitpoints[4];

	d[0] = get_ground_hit_point(home->sectors[bullet_sector], ray,
			&hitpoints[0]);
	d[1] = get_ceiling_hit_point(home->sectors[bullet_sector], ray,
			&hitpoints[1]);
	if (ray->side == ENEMY)
		d[3] = get_player_hit_point(ray, &hitpoints[3], bullet_sector);
	else if (ray->side == PLAYER)
		d[3] = get_entity_hit_point(home, ray, &hitpoints[3], bullet_sector);
	else
		d[3] = 400000000.0f;
	d[2] = get_wall_hit_point(home, ray, &hitpoints[2], bullet_sector);
	if (d[0] != 400000000.0f && d[0] <= d[1] && d[0] <= d[2] && d[0] <= d[3])
		return (hitpoints[0]);
	if (d[1] != 400000000.0f && d[1] <= d[0] && d[1] <= d[2] && d[1] <= d[3])
		return (hitpoints[1]);
	if (d[2] != 400000000.0f && d[2] <= d[1] && d[2] <= d[0] && d[2] <= d[3])
		return (hitpoints[2]);
	if (d[3] != 400000000.0f && d[3] <= d[1] && d[3] <= d[0] && d[3] <= d[2])
		return (hitpoints[3]);
	return (hitpoints[0]);
}

t_bullet_hole	get_bullet_hit_point(t_home *home, t_ray *ray,
		int bullet_sector)
{
	t_bullet_hole	hole;

	hole = loop_through_sector(home, ray, bullet_sector);
	hole.point = translate_point(&hole.point, vec3_mul(hole.normal, 0.15f));
	return (hole);
}
