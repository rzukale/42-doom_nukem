/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_functions.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:53:57 by tmaarela          #+#    #+#             */
/*   Updated: 2021/06/15 15:58:09 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_FUNCTIONS_H
# define PLAYER_FUNCTIONS_H

/*
** Player functions
*/

t_wall	*check_if_crossing(t_sector *sector, t_xyz pos);
t_xyz	check_y(t_sector *sector, t_player *plr, t_xyz pos);
int		check_y_diff(t_player *plr, t_xyz *test_pos, t_sector *to);
Uint32	check_distance_to_ceiling(t_sector *sector, t_xyz *new_loc);
float	check_distance_to_ground(t_sector *sector, t_player *plr, t_xyz pos);
void	crouch(t_player *plr);
void	gravity(t_sector *sector, t_player *plr, Uint32 delta_time);
void	init_player(t_player *plr);
int		jetpack(t_player *plr, t_home *home, Uint32 t);
void	jump(t_player *plr, t_sector *cur_sector);
int		player_move(t_player *plr, t_home *home, Uint32 delta_time);
int		plr_inside(t_sector *sector, t_xy *pos);
void	update_player(t_player *plr, t_home *home, Uint32 delta_time);
void	create_target_vector(t_player *plr);
#endif
