/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:51:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/08/26 10:31:28 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# define AGGRO_RANGE_1 10
# define AGGRO_RANGE_2 20
# define ENTITY_VELOCITY_1 0.0005f
# define ENTITY_VELOCITY_2 0.00025f
# define PROJECTILE_VELOCITY 50
# define ENEMY 99
# define PLAYER 33
# define ENTITY_WIDTH 128
# define ENTITY_HEIGH 128
# define SPRITE_COUNT 7
# define ENTITY_COOLDOWN_1 6
# define ENTITY_COOLDOWN_2 10
# define ENTITY_COOLDOWN_3 200
# define ENTITY_SPRITE_MOVE_START 0
# define ENTITY_SPRITE_MOVE_END 4
# define MAX_PROJECTILES 15

enum e_entities
{
	skull_skulker,
	thing,
	drone,
	crewmember,
	light_button,
	elevator_button,
	powerstation,
	lamp,
};

enum e_floors
{
	normal_room,
	elevator,
	lower,
	upper
};

enum e_door_states
{
	unlocked,
	locked,
	cleaning_keycard,
	engineering_keycard,
	military_keycard
};

enum e_hole_states
{
	nothing,
	player,
	ceiling_hole,
	ground_hole,
	wall_hole
};

enum e_entity_states
{
	in_front,
	front_left,
	left,
	back_left,
	back,
	back_right,
	right,
	front_right,
	attack,
	die_now
};

/*
** Entity functions
*/
void				activate_elevator(t_home *home, t_entity *entity, t_player *plr);
Uint32				attack_player(t_home *home, t_entity *entity, t_player *plr, Uint32 t);
void				bolt_elevator_doors(t_sector *sector, Uint32 state);
void				bolt_elevator_door(t_sector *elevator, t_sector **sectors,
					Uint32 previous_floor, Uint32 state);
Uint32				check_aggro(t_player *plr, t_entity *entity, t_sector *sector);
void				determine_angle_between_entity_and_plr(t_entity *entity, t_player *plr);
Uint32				die(t_entity *entity, Uint32 t);
int					entity_move(t_entity *entity, t_home *home, Uint32 t);
void				entity_chase(t_entity *entity, t_home *home, Uint32 t, t_player *plr);
void				entity_gravity(t_sector *sector, t_entity *entity, Uint32 delta_time);
float				get_distance_squared(t_xyz pt0, t_xyz pt1);
Uint32				handle_activation(t_entity *entity, t_home *home, t_player *plr);
void				initialize_projectile_triangles(t_projectile *projectile);
Uint32				initialize_entity_textures(t_entity *entity);
Uint32				lock_elevator(t_home *home, t_sector *elevator);
void				lock_the_door(t_wall *dimensions, t_wall *door);
void				pick_next_frame(t_entity *entity, Uint32 t);
void				rotate_projectile_based_on_axes(t_xyz normal,
						t_projectile *current);
void				set_bullet_hole(t_bullet_hole *hole, t_projectile *current);
void				set_entity_texels_for_frame(t_entity *entity);
Uint32				update_elevators(t_home *home, t_player *plr,
					Uint32 current_time, Uint32 delta_time);
void				update_enemies(t_home *home, t_player *plr, Uint32 delta_time);
void				update_projectiles(t_home *home, t_player *plr, Uint32 t);
Uint32				take_damage(t_entity *entity, Uint32 delta_time);
void				translate_entity(t_triangle *tri1, t_triangle *tri2,
						t_entity *entity);
void				translate_entities(t_home *home, float distance, int sector_idx);
Uint32				translate_sector(t_sector *sector, float distance);
void				turn_on_lights(t_entity *entity, t_home *home);
#endif
