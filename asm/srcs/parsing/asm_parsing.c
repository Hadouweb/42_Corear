#include "asm.h"

void				asm_parse_header(t_app *app)
{
	char	c;

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
			asm_put_error("Error : unexpected token");
	}
}

void				asm_save_cmd(t_app *app)
{
	t_node		*l;
	char		**tab;

	l = app->lst_line;
	while (l && l->n_line < (int)app->cursor->line)
		l = l->next;
	while (l)
	{
		tab = asm_strsplit(l->line);
		if (tab[0] && tab[0][0] != '\n')
			asm_check_cmd(app, tab);
		l = l->next;
	}
}

static unsigned int	asm_get_param_hex(t_param p)
{
	unsigned int	hex;

	hex = 0x0;
	if (p.str[0] == '%')
	{
		if (p.str[1] == ':')
			hex = 0x0;
		else
			hex = ft_atoi(&p.str[1]);
	}
	else if (p.str[0] == 'r')
		hex = ft_atoi(&p.str[1]);
	else
		hex = 0x0;
	return (hex);
}

void				asm_set_param_hex(t_app *app)
{
	t_btcode	*bt;
	int			i;

	bt = app->btcode;
	while (bt)
	{
		i = 0;
		while (i < 4)
		{
			if (bt->cmd->param[i].size)
				bt->cmd->param[i].hex = asm_get_param_hex(bt->cmd->param[i]);
			i++;
		}
		bt = bt->next;
	}
}

void				asm_parse(t_app *app)
{
	asm_parse_header(app);
	asm_save_cmd(app);
	asm_set_param_hex(app);
}
