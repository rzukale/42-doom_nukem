/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unfilter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:12:55 by rzukale           #+#    #+#             */
/*   Updated: 2021/02/18 16:15:01 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/png_parser.h"

void	convert_to_pixels(t_png *png)
{
	png->final_size = (png->height * png->width * png->bpp + 7) / 8;
	if (!(png->pixels = (unsigned char *)ft_memalloc(png->final_size)))
		error_output("Malloc error\n");
	if (png->bpp < 8 && png->bpp * png->width !=
		((png->width * png->bpp + 7) / 8) * 8)
	{
		unfilter_scanlines(png, png->inflated, png->inflated);
		remove_padding(png, png->pixels, png->inflated);
	}
	else
	{
		unfilter_scanlines(png, png->pixels, png->inflated);
	}
}

void	unfilter_scanlines(t_png *png, unsigned char *out, unsigned char *in)
{
	t_scan_helper	s;

	s.line = 0;
	s.prev = 0;
	s.byte_width = (png->bpp + 7) / 8;
	s.line_bytes = (png->width * png->bpp + 7) / 8;
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

void	setup_padding_helper(t_padding_helper *h, t_png *png)
{
	h->out_linebits = png->width * png->bpp;
	h->in_linebits = ((png->width * png->bpp + 7) / 8) * 8;
	h->difference = h->in_linebits - h->out_linebits;
	h->out_bit_p = 0;
	h->in_bit_p = 0;
	h->line = 0;
}

void	remove_padding(t_png *png, unsigned char *out, unsigned char *in)
{
	t_padding_helper h;

	setup_padding_helper(&h, png);
	while (h.line < png->height)
	{
		h.x = 0;
		while (h.x < h.out_linebits)
		{
			h.bit = (unsigned char)((in[(h.in_bit_p) >> 3] >>
				(7 - ((h.in_bit_p) & 0x7))) & 1);
			h.in_bit_p++;
			if (h.bit == 0)
				out[(h.out_bit_p) >> 3] |= (unsigned char)(~(1 << (7 -
						((h.in_bit_p) & 0x7))) & 1);
			else
				out[(h.out_bit_p) >> 3] |= (1 << (7 - ((h.out_bit_p) & 0x7)));
			h.out_bit_p++;
			h.x++;
		}
		h.in_bit_p += h.difference;
		h.line++;
	}
}

void	process_scanline(unsigned char *out,
	unsigned char *sl, t_scan_helper s)
{
	unsigned int i;

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