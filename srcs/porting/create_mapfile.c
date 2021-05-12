/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mapfile.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 11:15:57 by rzukale           #+#    #+#             */
/*   Updated: 2021/05/12 16:13:34 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

/*
** Separate functions for creating, writing to and reading from map files
** states: 0 = initialized; 1 = file creation done successfully;
** 2 = successfully wrote texture/audio/sector data to file
** [idx][width] [height] [size] [color_type] [color_depth]
** [format] [bits_per_pixel] [pitch] [compressed_size]
** [unsigned char *pixel data]
*/

unsigned char	*create_write_buffer(t_texture *tex)
{
	unsigned char	*buf;

	buf = NULL;
	buf = (unsigned char *)ft_strjoin(WRITE_BREAKER, ft_itoa(tex->idx));
	buf = (unsigned char *)ft_strjoin((const char *)buf, WRITE_BREAKER);
	buf = (unsigned char *)ft_strjoin((const char *)buf,
			ft_itoa(tex->source_size));
	buf = (unsigned char *)ft_strjoin((const char *)buf, WRITE_BREAKER);
	return (buf);
}

void	write_texture_data(int *fd, t_home *home)
{
	int				i;
	unsigned char	*buf;

	buf = NULL;
	buf = (unsigned char *)ft_strjoin("doom_textures #",
			(const char *)ft_itoa(home->nbr_of_textures));
	buf = (unsigned char *)ft_strjoin((const char *)buf, "\n");
	if (doom_write(fd, (const void **)&buf, ft_strlen((const char *)buf)) == -1)
			printf("failed to add texture numbers\n");
	ft_strdel((char **)&buf);
	i = 1;
	while (i <= home->nbr_of_textures)
	{
		buf = create_write_buffer(home->editor_tex[i]);
		if (buf == NULL)
			printf("failed to create write buffer\n");
		if (doom_write(fd, (const void **)&buf, ft_strlen((const char *)buf)) == -1)
			printf("failed to write texture\n");
		if (doom_write(fd, (const void **)&home->editor_tex[i]->source, home->editor_tex[i]->source_size) == -1)
			printf("failed to write texture\n");
		ft_strdel((char **)&buf);
		buf = (unsigned char *)ft_strnew(sizeof(unsigned char) * 2);
		buf = (unsigned char *)ft_strcpy((char *)buf, (const char *)"\n");
		if (doom_write(fd, (const void **)&buf, 1) == -1)
			printf("failed to write texture\n");
		ft_strdel((char **)&buf);
		i++;
	}
}

void	write_audio_data(int *fd, char *path, char *asset_name)
{
	t_audio_asset	asset;
	unsigned char	*tmp;

	get_audio_data(&asset, path);
	tmp = NULL;
	tmp = (unsigned char *)ft_strjoin((const char *)asset_name,
			(const char *)ft_itoa(asset.size));
	tmp = (unsigned char *)ft_strjoin((const char *)tmp, "\n");
	tmp = (unsigned char *)ft_strjoin((const char *)tmp, WRITE_BREAKER);
	if (doom_write(fd, (const void **)&tmp, ft_strlen((const char *)tmp)) == -1)
		printf("Failed to write audio data point start\n");
	if (doom_write(fd, (const void **)&asset.buf, asset.size) == -1)
		printf("Failed to write audio data\n");
	ft_strdel((char **)&tmp);
	tmp = (unsigned char *)ft_strnew(sizeof(unsigned char) * 2);
	tmp = (unsigned char *)ft_strcpy((char *)tmp, (const char *)"\n");
	if (doom_write(fd, (const void **)&tmp, 1) == -1)
		printf("failed to write texture\n");
	ft_strdel((char **)&tmp);
	free(tmp);
	free(asset.buf);
}

/*
**	Add writing map and audio data for the mapfile.
*/

int	create_map_file(t_home *home)
{
	int		fd;
	char	*tmp = "./map_files/test.DATA";

	doom_open(&fd, (const char**)&tmp,
		WRITE_ONLY | READ_ONLY | CREATE_FILE | TRUNCATE | CHECK_EXIST, 0644);
	if (fd < 0)
		return (-1);
	write_texture_data(&fd, home);
	write_audio_data(&fd, "./audio/eerie_by_eparviai.wav", "doom_music #");
	write_audio_data(&fd, "./audio/footstep1.wav", "doom_footstep1 #");
	write_audio_data(&fd, "./audio/footstep2.wav", "doom_footstep2 #");
	doom_close(&fd);
	return (1);
}

int		create_temp_audio_file(unsigned char *buf, ssize_t size, char *path)
{
	int		fd;

	doom_open(&fd, (const char **)&path,
		WRITE_ONLY | READ_ONLY | CREATE_FILE | TRUNCATE, 0644);
	if (fd < 0)
		return (-1);
	if (doom_write(&fd, (const void **)&buf, size) == -1)
		return (-1);
	if (doom_close(&fd) == -1)
		return (-1);
	return (1);
	
}

void	get_audio_data(t_audio_asset *asset, char *path)
{
	int				fd;

	asset->buf = (unsigned char *)malloc(sizeof(unsigned char) * MAX_SIZE);
	if (!asset->buf)
		error_output("Memory allocation of source buffer failed\n");
	doom_open(&fd, (const char **)&path, READ_ONLY, 0644);
	if (fd < 0)
		error_output("Failed to open file\n");
	else
	{
		doom_read((ssize_t *)&asset->size, &fd,
			(void **)&asset->buf, MAX_SIZE);
		if (asset->size <= 0)
			error_output("Failed to read file\n");
		else if (asset->size >= MAX_SIZE)
			error_output("File is too large\n");
		if (doom_close(&fd) == -1)
			error_output("Could not close file\n");
	}
}
