/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_push_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlouise <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 11:37:32 by dlouise           #+#    #+#             */
/*   Updated: 2016/02/21 11:38:15 by dlouise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_btcode		*asm_create_bt(void)
{
	t_btcode *bt;

	if ((bt = (t_btcode *)ft_memalloc(sizeof(t_btcode))) == NULL)
		asm_put_error("Error : Malloc CMD");
	bt->size_hex = 0;
	bt->cmd = NULL;
	bt->next = NULL;
	return (bt);
}

void			asm_push_bt(t_app *app, t_btcode *bt)
{
	t_btcode *btcode;

	btcode = app->btcode;
	if (btcode == NULL)
	{
		app->btcode = bt;
		return ;
	}
	while (btcode->next)
		btcode = btcode->next;
	btcode->next = bt;
}

static t_label	*asm_create_label(char *str)
{
	t_label	*label;

	if ((label = (t_label*)ft_memalloc(sizeof(t_label))) == NULL)
		asm_put_error("Error : Label not created");
	label->name = str;
	label->pos = -1;
	label->next = NULL;
	return (label);
}

void			asm_push_label(t_app *app, char *str)
{
	t_label	*l;

	l = app->label;
	if (l)
	{
		while (l->next)
			l = l->next;
		l->next = asm_create_label(str);
	}
	else
		app->label = asm_create_label(str);
}
