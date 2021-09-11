/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 11:23:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/11 16:38:52 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	editor_edit_wall(t_editor_walls *wall, t_action *action, int *nbr_of_walls, unsigned char **int_string)
{
	(void)nbr_of_walls;
	if (action->edit_ceiling_height || action->edit_floor_height)
	{
		read_input_string(int_string, action);
		if (!action->input_active)
		{
			if (action->edit_ceiling_height && *int_string)
			{
				wall->height.ceiling = ft_atoi((const char *)*int_string);
				if (wall->height.ceiling > 99)
					wall->height.ceiling = 99;
				if (wall->height.ceiling < -99)
					wall->height.ceiling = -99;
			}
			if (action->edit_floor_height && *int_string)
			{
				wall->height.ground = ft_atoi((const char *)*int_string);
				if (wall->height.ground > 99)
					wall->height.ground = 99;
				if (wall->height.ground < -99)
					wall->height.ground = -99;
			}
			if (*int_string)
				free(*int_string);
			*int_string = NULL;
			action->edit_wall = 0;
			action->edit_ceiling_height = 0;
			action->edit_floor_height = 0;
		}
	}
	if (action->change_wall_texture)
	{
		if (wall->type < 0)
		{
			if (wall->type == -wall0)
				wall->type = -wall1;
			else if (wall->type == -wall1)
				wall->type = -wall2;
			else if (wall->type == -wall2)
				wall->type = -wall3;
			else if (wall->type == -wall3)
				wall->type = -wall4;
			else if (wall->type == -wall4)
				wall->type = -wall5;
			else if (wall->type == -wall5)
				wall->type = -wall6;
			else if (wall->type == -wall6)
				wall->type = -wall7;
			else if (wall->type == -wall7)
				wall->type = -wall8;
			else if (wall->type == -wall8)
				wall->type = -wall9;
			else if (wall->type == -wall9)
				wall->type = -wall0;
		}
		action->change_wall_texture = 0;
		action->edit_wall = 0;
	}
}

void	editor_edit_sector(t_editor_sector *sector, t_action *action, unsigned char **int_string)
{
	if (action->change_ceiling_texture)
	{
		if (sector->tex_ceil == -surf0)
			sector->tex_ceil = -surf1;
		else if (sector->tex_ceil == -surf1)
			sector->tex_ceil = -surf2;
		else if (sector->tex_ceil == -surf2)
			sector->tex_ceil = -surf3;
		else if (sector->tex_ceil == -surf3)
			sector->tex_ceil = -surf4;
		else if (sector->tex_ceil == -surf4)
			sector->tex_ceil = -surf5;
		else if (sector->tex_ceil == -surf5)
			sector->tex_ceil = -surf6;
		else if (sector->tex_ceil == -surf6)
			sector->tex_ceil = -surf7;
		else if (sector->tex_ceil == -surf7)
			sector->tex_ceil = -surf8;
		else if (sector->tex_ceil == -surf8)
			sector->tex_ceil = -surf9;
		else if (sector->tex_ceil == -surf9)
			sector->tex_ceil = -surf0;
		action->change_ceiling_texture = 0;
		action->edit_sector = 0;
	}
	if (action->change_floor_texture)
	{
		if (sector->tex_floor == -surf0)
			sector->tex_floor = -surf1;
		else if (sector->tex_floor == -surf1)
			sector->tex_floor = -surf2;
		else if (sector->tex_floor == -surf2)
			sector->tex_floor = -surf3;
		else if (sector->tex_floor == -surf3)
			sector->tex_floor = -surf4;
		else if (sector->tex_floor == -surf4)
			sector->tex_floor = -surf5;
		else if (sector->tex_floor == -surf5)
			sector->tex_floor = -surf6;
		else if (sector->tex_floor == -surf6)
			sector->tex_floor = -surf7;
		else if (sector->tex_floor == -surf7)
			sector->tex_floor = -surf8;
		else if (sector->tex_floor == -surf8)
			sector->tex_floor = -surf9;
		else if (sector->tex_floor == -surf9)
			sector->tex_floor = -surf0;
		action->change_floor_texture = 0;
		action->edit_sector = 0;
	}
	if (action->set_light_intensity)
	{
		read_input_string(int_string, action);
		if (!action->input_active)
		{
			if (*int_string)
			{
				sector->light.intensity = ft_atoi((const char *)*int_string);
				if (sector->light.intensity > 100)
					sector->light.intensity = 100;
				if (sector->light.intensity < 0)
					sector->light.intensity = 0;
				free(*int_string);
				*int_string = NULL;
			}
			action->set_light_intensity = 0;
			action->edit_sector = 0;
		}
	}
	if (action->write_sector_story)
	{
		read_input_string(&sector->sector_plot, action);
		if (!action->input_active)
		{
			action->write_sector_story = 0;
			action->edit_sector = 0;
		}
	}
}

int		handle_events(t_editor *editor, t_home *home)
{
	editor->delta_time = SDL_GetTicks() - editor->cur_time;
	editor->cur_time = SDL_GetTicks();
	if (editor->action.edit_entity)
		edit_entity(editor->temp_entity, &editor->action);
	if (editor->action.unlink_entity)
	{
		unlink_selected_entity(&editor->entity_list,
			editor->action.selected_entity, &editor->action.unlink_entity);
	}
	if (editor->action.edit_wall && editor->temp_wall != NULL && editor->temp_sector != NULL)
		editor_edit_wall(editor->temp_wall, &editor->action, &editor->temp_sector->nb_of_walls, &editor->int_string);
	if (editor->action.edit_sector && editor->temp_sector != NULL)
		editor_edit_sector(editor->temp_sector, &editor->action, &editor->int_string);
	if (editor->action.create_sector == allocate)
	{
		editor_create_new_sector(&editor->sector_list, &editor->action);
		editor->action.create_sector++;
	}
	if (editor->action.create_sector == user_input)
	{
		if (editor_new_sector_wallpoints(&editor->sector_list,
			&editor->mouse_data, &editor->action))
			editor_free_selected_sector(&editor->sector_list,
				&editor->entity_list, &editor->action);
	}
	if (editor->action.save_file)
		save_editor_map(editor, home);
	if (editor->action.create_entity == user_input)
	{
		create_new_entity(&editor->entity_list, &editor->action,
			editor->temp_sector);
		editor->action.create_entity = idle;
	}
	if (editor->mouse_data.i_mbleft && !editor->action.input_active)
	{
		if (clicked_inside_ui(editor->mouse_data.x, editor->mouse_data.y,
				editor->buffer.height, editor->buffer.width))
		{
			check_ui_events(editor->mouse_data.x, editor->mouse_data.y,
				&editor->button_list, &editor->action);
			editor->mouse_data.i_mbleft = 0;
			if (editor->action.convert_to_portal == allocate && editor->temp_sector)
				editor->action.prev_sector = editor->temp_sector->idx_sector;
		}
		else if (clicked_inside_grid(editor->mouse_data.x, editor->mouse_data.y,
				editor->buffer.height, editor->buffer.width))
		{
			check_grid_events(editor);
			editor->mouse_data.i_mbleft = 0;
		}

	}
	if (editor->action.link_maps == 2)
		link_maps(&editor->action, &editor->linked_mapname, editor->map_names);
	if (editor->action.unlink_maps)
	{
		if (editor->linked_mapname)
		{
			free(editor->linked_mapname);
			editor->linked_mapname = NULL;
		}
		editor->action.unlink_maps = 0;
	}
	if (editor->action.open_file == 2)
		editor_load_map(editor);
	if (editor->notify_time)
		notify_user(&editor->notification, &editor->buffer,
			editor->delta_time, &editor->notify_time);
	return (1);
}
