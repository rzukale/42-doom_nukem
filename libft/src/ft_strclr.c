/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 16:18:59 by jnivala           #+#    #+#             */
/*   Updated: 2021/04/17 18:21:33 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_strclr(char *s)
{
	size_t	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i] != '\0')
		{
			s[i] = '\0';
			i++;
		}
	}
}
