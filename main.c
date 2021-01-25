/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 19:13:54 by tmaarela          #+#    #+#             */
/*   Updated: 2021/01/22 15:28:32 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int  			main(int argc, char **argv)
{
	t_home		home;
	t_player	plr;
	SDL_Event	e;

	// if (argc != 2)
	// 	error_output("usage: .\\play [map file name]\n");
	new_sector("sector00 4 5 10 -3 -4 40,200,1 250,200,2 200,0,1 90,0,-10\n");
	setup(argv[1], &home, &plr);
	update_sector(&home);
	while(1)
	{
		//home.t.beginfps = clock();
		update_player(&plr, &home, e);
		update_screen(&home, &plr);
		//fps = ft_itoa(home.t.fps);
		//SDL_SetWindowTitle(home.win.window, fps);
		//free(fps);
		SDL_UpdateWindowSurface(home.win.window);
		clear_surface(home.draw_surf);
		SDL_FreeSurface(home.draw_surf);
		//home.t.endfps = clock();
		//home.t.delta_time = home.t.endfps - home.t.beginfps;
		//home.t.fps = CLOCKS_PER_SEC / home.t.delta_time;
	}
	SDL_Quit();
	return 0;
}
