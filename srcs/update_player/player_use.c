/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_use.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 17:07:53 by jnivala           #+#    #+#             */
/*   Updated: 2021/10/07 13:09:02 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

t_bool	player_use(t_player *plr, t_home *home)
{
	t_entity		*entity;
	int				item;

	entity = NULL;
	if (!plr->input.use)
		return (false);
	if (plr->active_inv != -1)
		item = player_use_inventory_item(plr);
	else
		item = 0;
	open_door(home->sectors, plr, item);
	entity = activate_object(home, plr);
	if (entity)
	{
		handle_activation(entity, home, plr);
		plr->input.use = 0;
		return (true);
	}
	return (false);
}
