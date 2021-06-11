/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:24:36 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/11 16:26:22 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

// // void	gravity_func(t_player *plr, int floor_height, float gravity)
// // {
// // 	floor_height = floor_height;
// // 	// plr->z = plr->z - gravity;
// // 	if (plr->acceleration > 0)
// // 	{
// // 		plr->acceleration = plr->acceleration - gravity;
// // 		plr->height += plr->acceleration;
// // 	}
// // 	if (plr->acceleration < 0)
// // 	{
// // 		plr->acceleration = 0;
// // 		plr->height = 0;
// // 	}
// // }

static void	check_player_dir(t_player *plr)
{
	t_m4x4	matrix;

	if (plr->input.up == 1)
	{
		if (plr->input.left == 1)
			matrix = rotation_matrix_y(-0.7853982);
		else if (plr->input.right == 1)
			matrix = rotation_matrix_y(0.7853982);
		else
			matrix = rotation_matrix_y(0);
	}
	if (plr->input.down == 1)
	{
		if (plr->input.left == 1)
			matrix = rotation_matrix_y(-2.356194);
		else if (plr->input.right == 1)
			matrix = rotation_matrix_y(2.356194);
		else
			matrix = rotation_matrix_y(PI);
	}
	if (plr->input.left == 1 && plr->input.up == 0)
		matrix = rotation_matrix_y(-PI_BY_TWO);
	if (plr->input.right == 1 && plr->input.up == 0)
		matrix = rotation_matrix_y(PI_BY_TWO);
	plr->move_dir = multi_vec_matrix(&plr->look_dir, &matrix);
}

static void	movement(t_player *plr, t_home *home, Uint32 delta_time)
{
	if (plr->input.debug_up == 1)
		plr->pos.y += 0.05f;
	if (plr->input.debug_down == 1)
		plr->pos.y -= 0.05f;
	if (plr->input.debug_left == 1)
		plr->pos.x -= 0.05f;
	if (plr->input.debug_right == 1)
		plr->pos.x += 0.05f;
	if (plr->input.up == 1 || plr->input.down == 1
		|| plr->input.left == 1 || plr->input.right == 1)
	{
		check_player_dir(plr);
		if (player_move(plr, home, delta_time))
			play_footsteps(plr);
	}
}

void	update_player(t_player *plr, t_home *home, Uint32 delta_time)
{
	if (plr->input.rot_left == 1)
		plr->yaw -= 0.02f;
	if (plr->input.rot_right == 1)
		plr->yaw += 0.02f;
	crouch(plr, delta_time);
	movement(plr, home, delta_time);
}
