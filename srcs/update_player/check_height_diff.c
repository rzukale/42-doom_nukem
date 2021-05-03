/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_height_diff.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnivala <jnivala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:01:12 by jnivala           #+#    #+#             */
/*   Updated: 2021/05/03 14:24:15 by jnivala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/doom_nukem.h"

int	check_height_diff(t_sector *from, t_sector *to)
{
	if (from->ground - to->ground < -10)
		return (1);
	else if (to->ceiling - to->ground < 3)
		return (1);
	else
		return (0);
}
