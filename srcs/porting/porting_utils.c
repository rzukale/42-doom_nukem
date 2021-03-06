/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   porting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:55:06 by rzukale           #+#    #+#             */
/*   Updated: 2021/09/07 16:17:11 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

unsigned char	*create_write_buffer(t_texture *tex)
{
	unsigned char	*buf;

	buf = NULL;
	buf = (unsigned char *)ft_strjoin_freeable(WRITE_BREAKER,
			ft_itoa(tex->idx), 0, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			ft_itoa(tex->source_size), 1, 1);
	buf = (unsigned char *)ft_strjoin_freeable((char *)buf,
			WRITE_BREAKER, 1, 0);
	return (buf);
}

void	write_single_texture(t_texture *tex, int *fd, unsigned char *buf)
{
	buf = create_write_buffer(tex);
	if (buf == NULL)
		error_output("ERROR: Failed to create write buffer.");
	if (doom_write(fd, (const void **)&buf,
			ft_strlen((const char *)buf)) == -1)
		error_output("ERROR: Failed to write texture header.");
	if (doom_write(fd, (const void **)&tex->source,
			tex->source_size) == -1)
		error_output("ERROR: Failed to write texture data.");
	ft_strdel((char **)&buf);
	buf = (unsigned char *)ft_strnew(sizeof(unsigned char) * 2);
	buf = (unsigned char *)ft_strcpy((char *)buf, (const char *)"\n");
	if (doom_write(fd, (const void **)&buf, 1) == -1)
		error_output("ERROR: Failed to write texture end.");
	ft_strdel((char **)&buf);
}

int	get_next_breaker(unsigned char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == READ_BREAKER)
			return (i);
		i++;
	}
	return (-1);
}

t_texture	*return_new_texture(t_png *png, int idx)
{
	t_texture	*tex;

	parse_png(png);
	tex = create_texture(png, idx);
	free_png(*png);
	convert_to_uint32(tex->tex.texels, tex);
	return (tex);
}

void	free_all_textures(t_texture **textures, int nbr_of_textures)
{
	int	i;

	i = 0;
	while (i < nbr_of_textures)
		free_texture(textures[i++]);
	free(textures);
	textures = NULL;
}
