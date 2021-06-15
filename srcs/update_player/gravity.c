/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:13:41 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/15 16:01:33 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	gravity(t_sector *sector, t_player *plr, Uint32 delta_time)
{
	float			g;
	float			drop;
	static Uint32	total_time;

	g = 9.81f;
	drop = check_distance_to_ground(sector, plr, plr->pos);
	if (drop > 0.0f)
	{
		if (plr->input.jetpack)
			total_time = delta_time;
		else
			total_time += delta_time;
		drop = 0.5f * g * total_time * total_time * 0.000001f;
		plr->pos.y -= drop;
	}
	else
	{
		total_time = 0;
	}
	return ;
}
