/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 07:33:14 by mfroehly          #+#    #+#             */
/*   Updated: 2016/02/19 09:39:35 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	asm_strcmp_label(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*us1;
	unsigned char	*us2;

	i = 0;
	us1 = (unsigned char*)s1;
	us2 = (unsigned char*)s2;
	while (us1[i] == us2[i] && us1[i] != 0 && us2[i] != ':')
		i++;
	if (!us1[i] && us2[i] == ':')
		i--;
	return (us1[i] - us2[i]);
}

static void	asm_write_param(t_param *param)
{
	int		i;
	char	*p;

	i = param->size - 1;
	p = (char *)&param->hex;
	while (i >= 0)
	{
		ft_putchar_fd(p[i], 1);
		i--;
	}
}

static void	asm_set_label_dist(t_app *app, t_param *param, int pos)
{
	t_label		*l;

	l = app->label;
	if (param->str[0] == '%' && param->str[1] == ':')
	{
		while (l)
		{
			if (asm_strcmp_label(&param->str[2], l->name) == 0)
			{
				param->hex = l->pos - pos;
				return ;
			}
			l = l->next;
		}
		asm_put_error("Error : label not found");
	}
}

void		asm_write_data(t_app *app)
{
	t_btcode	*btcode;
	int			pos;
	int			i;

	pos = 0;
	btcode = app->btcode;
	while (btcode)
	{
		i = 0;
		ft_putchar_fd(btcode->cmd->instr.opcode, 1);
		if (btcode->cmd->instr.is_encoding)
			ft_putchar_fd(btcode->cmd->encoding, 1);
		while (i < 4 && btcode->cmd->param[i].size)
		{
			asm_set_label_dist(app, btcode->cmd->param + i, pos);
			asm_write_param(btcode->cmd->param + i);
			i++;
		}
		pos += btcode->cmd->cmd_size;
		btcode = btcode->next;
	}
}
