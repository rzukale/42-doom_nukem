/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:51:11 by tmaarela          #+#    #+#             */
/*   Updated: 2021/10/11 08:23:20 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H
# define MIN_RANGE 1.42f
# define MAX_RANGE 2.0f
# define STOMP_RANGE 0.2f
# define SNEAK_RANGE 0.5f
# define AGGRO_RANGE_1 10
# define AGGRO_RANGE_2 40
# define ENTITY_VELOCITY_1 0.0005f
# define ENTITY_VELOCITY_2 0.00025f
# define ENEMY 99
# define PLAYER 33
# define ATTACK_COOLDOWN 500
# define MOVE_COOLDOWN 200
# define SHOOT_COOLDOWN 400
# define ENTITY_SPRITE_MOVE_START 0
# define ENTITY_SPRITE_MOVE_END 4
# define MAX_PROJECTILES 15

enum e_help_text
{
	map_saving,
	story_string,
};

enum e_draw_depth
{
	depth_zero,
	sector,
	entity,
	wall,
};

enum e_entities
{
	skull_skulker,
	thing,
	drone,
	crewmember,
	light_button,
	lift_button,
	powerstation,
	lamp,
	ammo_pack,
	keycard_cleaning,
	keycard_engineering,
	keycard_military,
	poster
};

enum e_floors
{
	normal,
	lift,
	lower,
	upper
};

enum e_door_states
{
	unlocked = 300,
	locked = 301,
	cleaning_lock = 302,
	engineering_lock = 303,
	military_lock = 304
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
	on_left,
	back_left,
	back,
	back_right,
	on_right,
	front_right,
	attack,
	die_now
};

/*
** Entity functions
*/
void				activate_lift(t_home *home, t_entity *entity,
						t_player *plr);
t_bool				attack_player(t_home *home, t_entity *entity, t_player *plr,
						Uint32 t);
void				automatic_lights(t_sector *sector, t_home *home);
void				bolt_lift_doors(t_sector *sector, Uint32 state);
void				bolt_lift_door(t_sector *lift, t_sector **sectors,
						Uint32 previous_floor, Uint32 state);
void				change_texture(t_entity *entity);
t_bool				check_aggro(t_player *plr, t_entity *entity, t_home *home);
t_bool				check_if_entity_is_active(t_entity *entity);
void				determine_angle_between_entity_and_plr(t_entity *entity,
						t_player *plr);
t_bool				die(t_entity *entity, Uint32 t);
t_bool				entity_move(t_entity *entity, t_xyz plr_pos,
						t_home *home, Uint32 t);
void				entity_gravity(t_sector *sector, t_home *home,
						t_entity *entity, Uint32 delta_time);
t_bool				entity_bounce_off_player(t_entity *entity,
						t_home *home, Uint32 t);
t_bool				entity_bounce_off_the_wall(t_wall *wall, t_entity *entity,
						t_home *home, Uint32 t);
void				face_entity_towards_player(t_entity *entity);
float				get_distance_squared(t_xyz pt0, t_xyz pt1);
t_entity			*get_entity_with_sector_and_type(int sector_idx,
						t_uint type, t_home *home);
t_bool				handle_activation(t_entity *entity, t_home *home,
						t_player *plr);
t_bool				handle_keycards(t_entity *keycard);
void				initialize_triangle_index(t_triangle *tri,
						t_entity *entity);
void				initialize_entity_triangles(t_entity *entity);
void				initialize_projectile(t_projectile *projectile);
void				initialize_projectile_triangles(t_projectile *projectile);
void				initialize_entity_textures(t_entity *entity);
t_bool				is_enemy(int type);
t_bool				is_enemy_sprite(int type);
void				lock_lift(t_home *home, t_sector *lift);
void				lock_the_door(t_wall *dimensions, t_wall *door);
void				make_noise(t_entity *entity, t_player *plr, Uint32 t);
int					other_dir(int dir);
void				pick_next_frame(t_entity *entity, Uint32 t, int cooldown);
t_bool				pick_up_item(t_entity *item, t_home *home, t_player *plr);
void				place_entity_to_ground(t_entity *entity, t_home *home);
void				rotate_entity_towards_player(t_entity *entity,
						t_player *plr);
void				rotate_projectile_based_on_axes(t_xyz normal,
						t_projectile *current);
void				set_bullet_hole(t_bullet_hole *hole, t_projectile *current);
void				set_entity_texels_for_frame(t_entity *entity);
void				update_lifts(t_home *home, t_player *plr,
						Uint32 delta_time);
void				update_entities(t_home *home, t_player *plr,
						Uint32 delta_time);
void				update_projectiles(t_home *home, t_player *plr, Uint32 t);
t_bool				take_damage(t_entity *entity, Uint32 t);
void				translate_entity(t_triangle *tri1, t_triangle *tri2,
						t_entity *entity);
void				translate_entities(t_home *home, float distance,
						int sector_idx);
void				translate_projectiles(t_home *home, float distance,
						int sector_idx);
void				translate_sector(t_sector *sector, float distance);
void				turn_on_lights(t_entity *entity, t_home *home);
#endif
