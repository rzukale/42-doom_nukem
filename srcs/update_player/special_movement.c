/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 16:02:45 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/23 13:53:09 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static void	set_animation_on(Uint32 *start, Uint32 *end_time,
	Uint32 *current, Uint32 duration)
{
	if (!*start)
	{
		*start = 1;
		*end_time = *current + duration;
	}
}

static void	set_height(t_player *plr, char direction)
{
	if (direction == 'u')
	{
		plr->height += 0.1f;
		if (plr->height > 1.5f)
			plr->height = 1.5f;
		else
			plr->pos.y += 0.1f;
	}
	else if (direction == 'd')
	{
		plr->height -= 0.1f;
		if (plr->height <= 0.6f)
			plr->height = 0.6f;
		else
			plr->pos.y -= 0.1f;
	}
	else
		return ;
}

void	crouch(t_player *plr, t_sector *sector)
{
	static Uint32	animation_start = 0;
	static Uint32	animation_end = 0;

	if (plr->input.crouch == 1)
	{
		set_animation_on(&animation_start, &animation_end, &plr->time, 100);
		if (plr->time <= animation_end)
			set_height(plr, 'd');
		else
			animation_start = 0;
	}
	else if (plr->input.crouch == 0
		&& !check_distance_to_ceiling(sector, &plr->pos))
	{
		set_animation_on(&animation_start, &animation_end, &plr->time, 100);
		if (plr->time <= animation_end)
			set_height(plr, 'u');
		else
			animation_start = 0;
	}
	else
		return ;
}

void	jump(t_player *plr, t_sector *sector)
{
	float	dist;

	dist = 0.0f;
	check_distance_to_ground(sector, plr->height, plr->pos, &dist);
	if (plr->input.jump && dist <= 0.0f
		&& !check_distance_to_ceiling(sector, &plr->pos))
		plr->speed.y += 4.0f;
	if (check_distance_to_ceiling(sector, &plr->pos))
		plr->speed.y -= 4.0f;
	plr->input.jump = 0;
}

t_bool	jetpack(t_player *plr, t_home *home, Uint32 t)
{
	t_wall	*wall;

	if (plr->fuel_points > 1)
	{
		plr->fuel_points -= t * 0.05f;
		plr->move_dir = vec3_unit_vector(plr->look_dir);
		plr->test_pos = vec3_add(plr->pos, vec3_mul(plr->look_dir, t * 0.003f));
		if (check_distance_to_ceiling(home->sectors[plr->cur_sector],
				&plr->test_pos))
			return (false);
		wall = check_if_too_close_to_walls(home->sectors[plr->cur_sector],
				plr->width, plr->test_pos, plr->move_dir);
		if (!wall)
		{
			plr->pos = plr->test_pos;
			check_if_moved_through_portal(&plr->cur_sector, plr->pos, home);
			return (true);
		}
	}
	plr->input.jetpack = 0;
	return (false);
}
