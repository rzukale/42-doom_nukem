/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 13:36:50 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/24 12:04:03 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	render_buffer(Uint32 *buffer, SDL_Surface *screen_surface)
{
	SDL_LockSurface(screen_surface);
	optimized_memcpy(screen_surface->pixels,
		buffer, screen_surface->pitch * screen_surface->h);
	SDL_UnlockSurface(screen_surface);
}

void	update_screen(t_home *home, t_frame *frame, t_player *plr)
{
	(void)home;
	(void)plr;
	frame->last_frame = SDL_GetTicks();
	draw_cube(frame, home);
	// draw_frame(home, frame, plr);
}
