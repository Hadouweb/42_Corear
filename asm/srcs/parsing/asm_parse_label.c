#include "asm.h"

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

int		asm_isalnum(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ':')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			i++;
		else if (str[i] == '_')
			i++;
		else if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int			asm_check_label(t_app *app, char *str)
{
	int 	i;
	char	**tab;
	t_label *l;

	l = app->label;
	i = 0;
	tab = asm_strsplit(str);
	if (tab[0] && tab[0][ft_strlen(tab[0]) - 1] == ':')
	{
		if (!asm_isalnum(tab[0]))
			asm_put_error("Error : Syntax label2");
		while (l)
		{
			if (ft_strcmp(tab[0], l->name) == 0)
				asm_put_error("Error : Duplicate label");
			l = l->next;
		}
		asm_push_label(app, tab[0]);
		return (1);
	}
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == ':')
			asm_put_error("Error : Syntax label");
		i++;
	}
	return (0);
}

// en attente du header de David
/*void			asm_save_label(t_app *app)
{
	t_node	*l;

	l = app->lst_line;
	while (l && l->n_line < (int)app->cursor->line)
		l = l->next;
	while (l)
	{
		asm_check_label(app, l->line);
		l = l->next;
	}
}*/
