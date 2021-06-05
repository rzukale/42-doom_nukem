/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_to_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 11:58:40 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/05 10:59:50 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
**	Used if clause to no apparent effect.
*/
static void	calculate_distance_to_plane(t_xyz point, t_xyz plane_normal,
	 t_xyz plane_point, float *d)
{
	*d = plane_normal.x * point.x
		+ plane_normal.y * point.y
		+ plane_normal.z * point.z
		- vec3_dot_product(plane_normal, plane_point);
	// *d = vec3_dot_product(plane_normal, (vec3_dec(point, plane_point)));
}

static void	check_if_inside_triangle(float *d, t_point_location *loc,
	t_xyz point, t_uvz uv)
{
	if (*d >= 0)
	{
		loc->texels_inside[loc->inside] = uv;
		loc->points_inside[loc->inside] = point;
		loc->inside += 1;
	}
	else
	{
		loc->texels_outside[loc->outside] = uv;
		loc->points_outside[loc->outside] = point;
		loc->outside += 1;
	}
}

static int	form_a_triangle(t_point_location *loc, t_plane *plane,
	t_triangle *triangle1)
{
	triangle1->colour = white;
	triangle1->p[0] = loc->points_inside[0];
	triangle1->uv[0] = loc->texels_inside[0];
	triangle1->p[1] = vec3_intersection_with_plane(plane, loc->points_inside[0],
		loc->points_outside[0], &loc->texel_offset);
	triangle1->uv[1].u = loc->texel_offset * (loc->texels_outside[0].u
		- loc->texels_inside[0].u) + loc->texels_inside[0].u;
	triangle1->uv[1].v = loc->texel_offset * (loc->texels_outside[0].v
		- loc->texels_inside[0].v) + loc->texels_inside[0].v;
	triangle1->uv[1].w = loc->texel_offset * (loc->texels_outside[0].w
		- loc->texels_inside[0].w) + loc->texels_inside[0].w;
	triangle1->p[2] = vec3_intersection_with_plane(plane, loc->points_inside[0],
		loc->points_outside[1], &loc->texel_offset);
	triangle1->uv[2].u = loc->texel_offset * (loc->texels_outside[1].u
		- loc->texels_inside[0].u) + loc->texels_inside[0].u;
	triangle1->uv[2].v = loc->texel_offset * (loc->texels_outside[1].v
		- loc->texels_inside[0].v) + loc->texels_inside[0].v;
	triangle1->uv[2].w = loc->texel_offset * (loc->texels_outside[1].w
		- loc->texels_inside[0].w) + loc->texels_inside[0].w;
	return (1);
}

static int	form_a_quadrant(t_point_location *loc, t_plane *plane,
	t_triangle *triangle1, t_triangle *triangle2)
{
		triangle1->colour = white;
		triangle1->p[0] = loc->points_inside[0];
		triangle1->uv[0] = loc->texels_inside[0];
		triangle1->p[1] = loc->points_inside[1];
		if (loc->points_inside[0].x < plane->point.x && plane->normal.x == 1.0f)
			triangle1->colour = white;
		triangle1->uv[1] = loc->texels_inside[1];
		triangle1->p[2] = vec3_intersection_with_plane(plane, loc->points_inside[0],
			loc->points_outside[0], &loc->texel_offset);
		triangle1->uv[2].u = loc->texel_offset * (loc->texels_outside[0].u
			- loc->texels_inside[0].u) + loc->texels_inside[0].u;
		triangle1->uv[2].v = loc->texel_offset * (loc->texels_outside[0].v
			- loc->texels_inside[0].v) + loc->texels_inside[0].v;
		triangle1->uv[2].w = loc->texel_offset * (loc->texels_outside[0].w
			- loc->texels_inside[0].w) + loc->texels_inside[0].w;
		triangle2->p[0] = loc->points_inside[1];
		triangle2->uv[0] = loc->texels_inside[1];
		triangle2->p[1] = triangle1->p[2];
		triangle2->uv[1] = triangle1->uv[2];
		triangle2->p[2] = vec3_intersection_with_plane(plane, loc->points_inside[1],
			loc->points_outside[0], &loc->texel_offset);
		triangle2->uv[2].u = loc->texel_offset * (loc->texels_outside[0].u
			- loc->texels_inside[1].u) + loc->texels_inside[1].u;
		triangle2->uv[2].v = loc->texel_offset * (loc->texels_outside[0].v
			- loc->texels_inside[1].v) + loc->texels_inside[1].v;
		triangle2->uv[2].w = loc->texel_offset * (loc->texels_outside[0].w
			- loc->texels_inside[1].w) + loc->texels_inside[1].w;
		return (2);
}

int		clip_against_plane(t_plane *plane, t_triangle *src,
		t_triangle *triangle1, t_triangle *triangle2)
{
	t_point_location	loc;
	float				d[3];

	initialize_locations(&loc);
	plane->normal = vec3_unit_vector(plane->normal);
	calculate_distance_to_plane(src->p[0], plane->normal, plane->point, &d[0]);
	calculate_distance_to_plane(src->p[1], plane->normal, plane->point, &d[1]);
	calculate_distance_to_plane(src->p[2], plane->normal, plane->point, &d[2]);
	check_if_inside_triangle(&d[0], &loc, src->p[0], src->uv[0]);
	check_if_inside_triangle(&d[1], &loc, src->p[1], src->uv[1]);
	check_if_inside_triangle(&d[2], &loc, src->p[2], src->uv[2]);
	if (loc.inside == 0)
		return (0);
	if (loc.inside == 3)
	{
		*triangle1 = *src;
		return (1);
	}
	if (loc.inside == 1 && loc.outside == 2)
		return (form_a_triangle(&loc, plane, triangle1));
	if (loc.inside == 2 && loc.outside == 1)
		return (form_a_quadrant(&loc, plane, triangle1, triangle2));
	return (0);
}
