/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_initstruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromny-w <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 20:49:27 by aromny-w          #+#    #+#             */
/*   Updated: 2019/05/26 20:49:28 by aromny-w         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_initstruct(t_pf *info)
{
	info->flags.hash = 0;
	info->flags.zero = 0;
	info->flags.minus = 0;
	info->flags.space = 0;
	info->flags.plus = 0;
	info->width = 0;
	info->prec = -1;
	info->mods.hh = 0;
	info->mods.h = 0;
	info->mods.l = 0;
	info->mods.ll = 0;
	info->mods.j = 0;
	info->mods.t = 0;
	info->mods.z = 0;
	info->mods.q = 0;
	info->spec = '\0';
}
