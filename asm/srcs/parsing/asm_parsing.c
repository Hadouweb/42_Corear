/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 07:24:51 by nle-bret          #+#    #+#             */
/*   Updated: 2016/02/23 07:24:53 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_parse_header(t_app *app)
{
	char	c;

	app->header.magic = asm_reverse_uint(COREWAR_EXEC_MAGIC);
	while (1)
	{
		c = asm_read_char(app);
		if (c == ' ' || c == '\t' || c == '\n')
			continue ;
		else if (c == '#' || c == ';')
		{
			c = asm_read_char(app);
			while (c != '\n')
				c = asm_read_char(app);
		}
		else if (c == '.')
		{
			if (asm_read_directive(app))
				break ;
		}
		else
			asm_put_error_char_int_int("Error : unexpected token ", c,
					app->cursor->line, app->cursor->col);
	}
}

void	asm_save_cmd(t_app *app)
{
	t_node		*n;
	t_label		*l;

	n = app->lst_line;
	l = app->label;
	while (n && n->n_line + 1 < (int)app->cursor->line)
		n = n->next;
	while (n)
	{
		asm_check_line(app, n->line, n->n_line);
		n = n->next;
	}
}

void	asm_parse(t_app *app)
{
	asm_parse_header(app);
	asm_delete_comment_after_header(app);
	asm_save_cmd(app);
}
