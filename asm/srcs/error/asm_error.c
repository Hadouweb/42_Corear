/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 07:25:29 by nle-bret          #+#    #+#             */
/*   Updated: 2016/02/23 07:25:31 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_check_line(t_app *app, char *str, int line)
{
	int			i;
	t_btcode	*bt;

	i = 0;
	bt = asm_create_bt();
	str += asm_dodge_space_tab(str);
	if (*str)
	{
		asm_error_label(&str, app);
		asm_update_label_pos(app);
		if (!*str)
			return ;
		asm_error_instr(&str, app, line, bt);
		asm_error_param(&str, line, bt);
		if (*str)
			asm_put_error_line(str, line);
		asm_push_bt(app, bt);
		app->byte_count += bt->cmd->cmd_size;
	}
}

t_instr	asm_get_instr(t_app *app, int i_instr)
{
	int		i;

	i = 0;
	while (i < 16 && i != i_instr)
		i++;
	return (app->instr[i]);
}
