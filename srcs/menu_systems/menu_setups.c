/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_setups.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 10:17:34 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/03 16:27:29 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	get_map_count(int *count, DIR **dir, struct dirent **dir_entry)
{
	char	*found;

	*dir_entry = readdir(*dir);
	while (*dir_entry != NULL)
	{
		found = ft_strstr((*dir_entry)->d_name, ".TEST");
		if (found != NULL)
			(*count)++;
		*dir_entry = readdir(*dir);
	}
	rewinddir(*dir);
	if ((*count) == 0)
	{
		printf("no maps to load\n");
		closedir(*dir);
		return (-1);
	}
	return (1);
}

void	load_map_names(t_menu *menu)
{
	DIR				*dir;
	struct dirent	*dir_entry;

	dir = opendir("map_files/");
	if (dir == NULL)
		error_output("Failed to open map_files directory.\n");
	if (get_map_count(&menu->nbr_of_maps, &dir, &dir_entry) == -1)
		return ;
	menu->map_names = (char **)malloc(sizeof(char *) * (menu->nbr_of_maps));
	if (!menu->map_names)
		error_output("Failed to allocate memory to map file names.\n");
	dir_entry = readdir(dir);
	loop_map_names(menu->map_names, dir_entry, dir);
	closedir(dir);
}

void	setup_menu(t_menu *menu, int *game_state)
{
	menu->nbr_of_maps = 0;
	menu->menu_buffer = (Uint32 *)malloc(sizeof(Uint32)
			* (SCREEN_WIDTH * SCREEN_HEIGHT));
	if (!menu->menu_buffer)
		error_output("Failed to allocate memory to menu_buffer\n");
	menu->option = 0;
	*game_state = MAIN_MENU;
}

// REVISIT PUT MUSIC TOGGLE
// if (Mix_PlayingMusic() == 0)
// 	Mix_PlayMusic(plr->audio.music, -1);
void	setup_game_loop(t_home *home, t_player *plr, int *menu_option)
{
	ft_putstr("You chose: ");
	ft_putendl_fd(home->chosen_map, 1);
	initialize_player(plr);
	if (initialize_skybox(&home->skybox))
		error_output("Memory allocation failed!\n");
	if (initialize_hud(&plr->hud))
		error_output("Memalloc failed for HUD\n");
	if (load_map_file(plr, home))
		error_output("Error while loading map!\n");
	home->nbr_of_textures = NUM_TEX;
	init_textures(home);
	if (load_game_audio(&plr->audio))
	{
		free_game_assets(home);
		home->game_state = MAIN_MENU;
		return ;
	}
	if (setup_fps(&home->t))
		error_output("Memory allocation failed!\n");
	*menu_option = 0;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	home->game_state = GAME_LOOP;
}

void	setup_editor(t_home *home)
{
	init_textures(home);
}
