/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:08:38 by jnivala           #+#    #+#             */
/*   Updated: 2021/06/15 14:38:43 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECTOR_H
# define SECTOR_H

typedef struct s_wall
{
	t_triangle			top;
	t_triangle			bottom;
	float				wall_facing;
	t_xy				normal;
	struct s_wall		*next;
}						t_wall;

typedef struct s_surface
{
	t_triangle			tri;
	float				wall_facing;
	t_xy				normal;
	struct s_surface	*next;
}						t_surface;

typedef struct s_skybox
{
	int					idx;
	t_triangle			*face;
}						t_skybox;

typedef struct s_point_data
{
	float		x;
	float		y;
	int			ground;
	int			ceiling;
	int			idx;
}				t_point_data;

typedef struct s_sector
{
	t_wall			*walls;
	unsigned int	nb_of_walls;
	unsigned int	nb_of_ceil;
	unsigned int	nb_of_ground;
	int				idx_sector;
	int				tex_floor;
	int				tex_ceil;
	t_surface		*ground;
	t_surface		*ceiling;
}					t_sector;

enum e_sector_info
{
	old_sector = -6666
};

t_wall			*new_point(t_point_data *left, t_point_data *right);
void			add_point(t_wall **point, t_wall *new);

#endif
