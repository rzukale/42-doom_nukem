/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_points2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 13:05:47 by tmaarela          #+#    #+#             */
/*   Updated: 2021/09/29 13:38:08 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	editor_reset_wall_indexes(t_editor_walls **walls, int nbr_of_walls)
{
	t_editor_walls	*temp;
	int				idx;

	temp = *walls;
	idx = 0;
	while (idx < nbr_of_walls)
	{
		temp->idx = idx;
		temp = temp->next;
		idx++;
	}
}

void	add_point_end(t_editor_walls **point, t_editor_walls *new)
{
	t_editor_walls	*temp;
	int				i;

	i = 0;
	if (new == NULL)
		return ;
	if (*point == NULL)
	{
		new->idx = i;
		*point = new;
	}
	else
	{
		temp = *point;
		while (temp->next != NULL)
		{
			i++;
			temp = temp->next;
		}
		i++;
		new->idx = i;
		temp->next = new;
		new->next = NULL;
	}
}

static void	assign_final_bboxes(t_editor_sector *sector,
	t_screen_xy min, t_screen_xy max)
{
	sector->bbox.start.x = min.x;
	sector->bbox.start.y = max.y;
	sector->bbox.end.x = max.x;
	sector->bbox.end.y = min.y;
}

void	assign_sector_bbox(t_editor_sector *sector)
{
	t_screen_xy		min;
	t_screen_xy		max;
	t_editor_walls	*temp;
	int				i;

	i = 0;
	min = (t_screen_xy){5000, 5000};
	max = (t_screen_xy){-5000, -5000};
	temp = sector->walls;
	while (i < sector->nb_of_walls && temp != NULL)
	{
		if (min.x > temp->x0.x)
			min.x = temp->x0.x;
		if (min.y > temp->x0.y)
			min.y = temp->x0.y;
		if (max.x < temp->x0.x)
			max.x = temp->x0.x;
		if (max.y < temp->x0.y)
			max.y = temp->x0.y;
		temp = temp->next;
		i++;
	}
	assign_final_bboxes(sector, min, max);
}

t_editor_walls	*new_wall_point(t_screen_xy world_coord)
{
	t_editor_walls	*new;

	new = (t_editor_walls *)malloc(sizeof(*new));
	if (new != NULL)
	{
		new->x0.x = world_coord.x;
		new->x0.y = world_coord.y;
		new->idx = -1;
		new->type = -wall0;
		new->bbox.start = vec2(new->x0.x - 0.2f, new->x0.y + 0.2f);
		new->bbox.end = vec2((new->x0.x + 0.2f), (new->x0.y - 0.2f));
		new->height.ground = 0;
		new->height.ceiling = 3;
		new->next = NULL;
	}
	else
	{
		free(new);
		new = NULL;
	}
	return (new);
}
