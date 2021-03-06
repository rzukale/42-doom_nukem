/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_noise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:11:42 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/08 18:04:45 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

static int	noise_logic(float dist)
{
	int	volume;

	if (dist <= 49.0f && dist > 36.0f)
		volume = 10;
	else if (dist <= 36.0f && dist > 25.0f)
		volume = 15;
	else if (dist <= 25.0f && dist > 16.0f)
		volume = 20;
	else if (dist <= 16.0f && dist > 9.0f)
		volume = 25;
	else if (dist <= 9.0f && dist > 4.0f)
		volume = 30;
	else if (dist <= 4.0f && dist > 1.0f)
		volume = 40;
	else
		volume = 0;
	return (volume);
}

void	make_noise(t_entity *entity, t_player *plr, Uint32 t)
{
	float	dist;
	int		volume;

	if (entity->making_noise <= 0)
	{
		dist = get_distance_squared(plr->pos, entity->pos);
		if (dist >= 49.0f || dist <= 1.0f)
			return ;
		entity->making_noise = 10000;
		volume = noise_logic(dist);
		if (entity->type == skull_skulker && !entity->is_revealed)
			play_sound(plr->audio.skull_skulker_lulling, volume);
		else if (entity->type == thing && !entity->is_revealed)
			play_sound(plr->audio.thing_lulling, volume);
		else
			play_sound(plr->audio.rahikainen_ramble[1], volume);
	}
	else
		entity->making_noise -= t;
}
