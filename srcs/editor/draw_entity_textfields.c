/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_entity_textfields.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:07:32 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/15 18:08:10 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	draw_multisprite_image(t_xy offset, t_texel *tex,
	t_buffer *buffer, t_xy scale)
{
	t_screen_xy	current;

	current.x = 0;
	current.y = 0;
	scale.w = 1 / scale.w;
	while (current.y < scale.y)
	{
		current.x = 0;
		while (current.x < scale.x)
		{
			put_pixel(
				buffer,
				(t_pxl_coords){current.x + offset.x,
				current.y + offset.y},
				(Uint32)tex->texels[(tex->width * current.y
					* (int)scale.w) + current.x * (int)scale.w]);
			current.x++;
		}
		current.y++;
	}
}

static void	draw_entity_textures(t_entity_list *entity,
	t_buffer *buffer, t_texture **textures)
{
	t_texel			*tex;
	t_xy			scale;
	t_box			box;

	box.start = vec2(32, 110);
	box.end = vec2(132, 220);
	draw_box(box, buffer, get_color(black));
	tex = get_tex(editor_select_entity_tex(entity->entity_type), textures);
	if (entity->entity_type == skull_skulker || entity->entity_type == thing
		|| entity->entity_type == drone || entity->entity_type == crewmember)
	{
		scale.w = (float)(ft_fabsf(box.end.x - box.start.x) / 128);
		scale.x = 128;
		scale.y = 128;
		draw_multisprite_image(box.start, tex, buffer, scale);
	}
	else
	{
		scale.w = (float)(ft_fabsf(box.end.x - box.start.x) / tex->width);
		draw_image(box.start, tex, buffer, scale.w);
	}
}

void	draw_entity_textfields(t_entity_list *entity,
	t_buffer *buffer, t_texture **textures)
{
	t_plx_modifier	mod;
	char			*str;

	if (!entity)
		return ;
	mod.colour = get_color(white);
	mod.size = TEXT_SIZE;
	str = ft_itoa(entity->entity_idx);
	mod.len = ft_strlen(str) + 1;
	ft_str_pxl(buffer, vec2(165, 56), str, mod);
	ft_strdel(&str);
	str = ft_itoa(entity->entity_type);
	mod.len = ft_strlen(str) + 1;
	ft_str_pxl(buffer, vec2(165, 84), str, mod);
	ft_strdel(&str);
	mod.len = 1;
	ft_c_pxl(buffer, vec2(165, 229), '0' + entity->is_linked, mod);
	ft_c_pxl(buffer, vec2(165, 259), '0' + entity->is_revealed, mod);
	ft_c_pxl(buffer, vec2(165, 289), '0' + entity->is_static, mod);
	ft_c_pxl(buffer, vec2(165, 325), '0' + entity->state, mod);
	draw_entity_textures(entity, buffer, textures);
}
