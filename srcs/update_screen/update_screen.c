#include "../../doom_nukem.h"

void	update_screen(t_home *home, t_player *plr)
{
	draw_fov(home, plr);
	draw_minimap(home->map.size, plr->pos, plr->dir, home);
}