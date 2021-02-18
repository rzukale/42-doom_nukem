/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_visible_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:22:33 by jnivala           #+#    #+#             */
/*   Updated: 2021/02/18 14:44:55 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../doom_nukem.h"

int		calc_visible_walls(t_sector *sector)
{
	int			visible_walls;
	int			walls;
	t_point		*temp;

	visible_walls = 0;
	walls = sector->nb_of_walls;
	temp = sector->points;
	while (walls)
	{
		if ((temp->x0.y >= 0 && temp->x0.x >= 0) ||
			(temp->next->x0.y >= 0 && temp->x0.x >= 0))
			visible_walls++;
		temp = temp->next;
		walls--;
	}
	return (visible_walls);
}