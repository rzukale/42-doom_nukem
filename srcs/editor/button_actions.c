/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:11:16 by rzukale           #+#    #+#             */
/*   Updated: 2021/10/11 08:13:21 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	main_button_actions(t_action *action, int i)
{
	if (i == button_save)
	{
		action->save_file = true;
		if (!action->map_name_set)
			action->input_active = true;
	}
	else if (i == button_open && action->nbr_of_maps > 0)
		action->open_file = 1;
	else if (i == button_activate_grid)
	{
		if (action->grid)
			action->grid = false;
		else
			action->grid = true;
	}
	else if (i == button_assign_end_sector)
		action->assign_end_sector = allocate;
	else if (i == button_link_map && action->nbr_of_maps > 0)
		action->link_maps = 1;
	else if (i == button_unlink_map)
		action->unlink_maps = 1;
	else if (i == button_plr_start)
		action->assign_player_start = allocate;
}

static void	sector_button_actions_two(t_action *action, int i)
{
	if (i == button_create_portal)
		action->convert_to_portal = allocate;
	else if (i == button_set_all_ceiling_heights)
	{
		action->set_all_sector_ceiling_heights = true;
		action->input_active = true;
	}
	else if (i == button_set_all_floor_heights)
	{
		action->set_all_sector_floor_heights = true;
		action->input_active = true;
	}
	else if (i == button_set_gravity)
	{
		action->set_gravity = true;
	}
}

void	sector_button_actions(t_action *action, int i)
{
	action->edit_sector = 1;
	if (i == button_change_floor_tex)
		action->change_floor_texture = true;
	else if (i == button_change_ceil_tex)
		action->change_ceiling_texture = true;
	else if (i == button_set_light_intensity)
	{
		action->input_active = true;
		action->set_light_intensity = true;
	}
	else if (i == button_convert_to_elevator)
		action->create_elevator = true;
	else if (i == button_create_light_src)
		action->create_light_source = true;
	else if (i == button_input_active)
	{
		action->write_sector_story = true;
		action->input_active = true;
	}
	sector_button_actions_two(action, i);
}

void	entity_button_actions(t_action *action, int i)
{
	action->edit_entity = 1;
	if (i == button_change_entity_type)
		action->change_entity_type = true;
	else if (i == button_toggle_entity_is_linked)
		action->toggle_entity_is_linked = true;
	else if (i == button_toggle_entity_is_revealed)
		action->toggle_is_revealed = true;
	else if (i == button_toggle_state)
		action->toggle_state = true;
}

void	wall_button_actions(t_action *action, int i)
{
	action->edit_wall = true;
	if (i == button_change_wall_tex)
		action->change_wall_texture = true;
	else if (i == button_set_ceiling_height)
	{
		action->edit_ceiling_height = true;
		action->input_active = true;
	}
	else if (i == button_set_floor_height)
	{
		action->edit_floor_height = true;
		action->input_active = true;
	}
	else if (i == button_create_light_button)
		action->create_light_button = true;
	else if (i == button_create_powerstation)
		action->create_powerstation = true;
	else if (i == button_create_elevator_button)
		action->create_elev_button = true;
	if (i == button_change_to_door)
		action->cycle_portal = true;
	if (i == button_add_poster)
		action->add_poster = true;
}
