/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_join_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/20 05:25:54 by mfroehly          #+#    #+#             */
/*   Updated: 2016/02/21 07:07:14 by atrupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_join_arg(t_app *app, char **tab, int i)
{
	int		j;
	char	*ret;
	char	*tmp;

	if (tab[i] == NULL)
		asm_put_error("Error : No argument after instruction");
	j = i;
	ret = ft_strdup("");
	while (tab[j])
	{
		if (asm_check_label(app, tab[j]) || asm_is_instr(app, tab[j]))
			asm_put_error("Error : Bad argument");
		tmp = ft_strjoin(ret, tab[j]);
		free(ret);
		ret = tmp;
		free(tab[j]);
		tab[j] = 0;
		j++;
	}
	tab[i] = ret;
}
