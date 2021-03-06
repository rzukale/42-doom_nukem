/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sector_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:29:17 by jnivala           #+#    #+#             */
/*   Updated: 2021/09/27 13:19:25 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	initialize_sector_pointers(t_sector *new_sector)
{
	new_sector->walls = NULL;
	new_sector->ceiling = NULL;
	new_sector->ground = NULL;
	new_sector->story = NULL;
}

void	initialize_wall_triangles(t_wall *wall, t_point_data *left,
	t_point_data *right)
{
	wall->top.p[0] = (t_xyz){left->x, left->ground, left->y, 1.0f};
	wall->top.p[1] = (t_xyz){left->x, left->ceiling, left->y, 1.0f};
	wall->top.p[2] = (t_xyz){right->x, right->ceiling, right->y, 1.0f};
	wall->bot.p[0] = (t_xyz){left->x, left->ground, left->y, 1.0f};
	wall->bot.p[1] = (t_xyz){right->x, right->ceiling, right->y, 1.0f};
	wall->bot.p[2] = (t_xyz){right->x, right->ground, right->y, 1.0f};
}

int	get_door_lock(int door_idx)
{
	if (door_idx == -door
		|| (door_idx >= DOOR_INDEX && door_idx < CLEANING_INDEX))
		return (unlocked);
	else if (door_idx >= CLEANING_INDEX && door_idx < ENGINEERING_INDEX)
		return (cleaning_lock);
	else if (door_idx >= ENGINEERING_INDEX && door_idx < MILITARY_INDEX)
		return (engineering_lock);
	else if (door_idx >= MILITARY_INDEX && door_idx < SECRET_INDEX)
		return (military_lock);
	else if (door_idx >= SECRET_INDEX && door_idx < SMALL_WINDOW_INDEX)
		return (unlocked);
	else
		return (locked);
}

void	initialize_door(t_wall *wall, t_point_data *left, t_point_data *right)
{
	wall->top.type = change_door_to_portal(left->idx);
	wall->bot.type = change_door_to_portal(left->idx);
	wall->is_door = 0;
	wall->is_window = 0;
	wall->is_closed = false;
	wall->open_until = 0;
	wall->height = get_wall_height(left->ground, right->ground,
			left->ceiling, right->ceiling);
	if (left->idx >= DOOR_INDEX)
	{
		if (left->idx >= LARGE_WINDOW_INDEX)
			wall->is_window = 2;
		else if (left->idx >= SMALL_WINDOW_INDEX)
			wall->is_window = 1;
		else if (left->idx >= SECRET_INDEX)
			wall->is_door = 2;
		else
			wall->is_door = 1;
		wall->is_locked = get_door_lock(left->idx);
	}
}

void	add_to_middle(t_wall **current_point, t_wall *new_wall)
{
	t_wall	*temp;

	if (new_wall == NULL)
		return ;
	if (*current_point == NULL)
	{
		*current_point = new_wall;
	}
	else
	{
		temp = (*current_point)->next;
		(*current_point)->next = new_wall;
		new_wall->next = temp;
	}
}
