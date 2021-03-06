/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unfilter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:12:55 by rzukale           #+#    #+#             */
/*   Updated: 2021/07/22 14:09:23 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

void	convert_to_pixels(t_png *png)
{
	png->final_size = ((png->width * png->channels) * png->height) + 1;
	png->pixels = (unsigned char *)ft_memalloc(sizeof(unsigned char)
			* png->final_size);
	if (!png->pixels)
		error_output("Memory allocation of filtered pixel pointer failed.");
	unfilter_scanlines(png, png->pixels, png->inflated);
}

void	unfilter_scanlines(t_png *png, unsigned char *out, unsigned char *in)
{
	t_scan_helper	s;

	s.line = 0;
	s.prev = 0;
	s.byte_width = png->channels;
	s.line_bytes = (png->width * png->channels);
	while (s.line < png->height)
	{
		s.out_index = s.line_bytes * s.line;
		s.in_index = (1 + s.line_bytes) * s.line;
		s.filter = in[s.in_index];
		if (s.filter > 4)
			error_output("filtering error\n");
		process_scanline(&out[s.out_index], &in[s.in_index + 1], s);
		s.prev = &out[s.out_index];
		s.line++;
	}
}

void	process_scanline(unsigned char *out,
	unsigned char *sl, t_scan_helper s)
{
	int	i;

	if (s.filter == 0)
	{
		i = 0;
		while (i++ < s.line_bytes)
			out[i] = sl[i];
	}
	else if (s.filter == 1)
	{
		sub(out, sl, s);
	}
	else if (s.filter == 2)
	{
		up(out, sl, s);
	}
	else if (s.filter == 3)
	{
		avg(out, sl, s);
	}
	else if (s.filter == 4)
	{
		paeth(out, sl, s);
	}
}
