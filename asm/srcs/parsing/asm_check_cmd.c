#include "asm.h"

int			asm_is_label(t_app *app, char *str)
{
	t_label		*l;

	l = app->label;
	if (!str)
		return (0);
	while (l)
	{
		if (ft_strcmp(l->name, str) == 0)
			return (1);
		l = l->next;
	}
	return (0);
}

int			asm_is_instr(t_app *app, char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (i < 16)
	{
		if (ft_strcmp(app->instr[i].name, str) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	asm_error_label(t_app *app, char *label)
{
	t_label *l;

	l = app->label;
	if (!asm_isalnum(label))
		asm_put_error("Error : Syntax label");
	while (l)
	{
		if (ft_strcmp(label, l->name) == 0)
			asm_put_error("Error : Duplicate label");
		l = l->next;
	}
	asm_push_label(app, label);
	return (1);
}

static int	asm_check_label(t_app *app, char *str)
{
	int		i;
	char	**tab;

	i = 0;
	tab = asm_strsplit(str);
	if (tab[0] && tab[0][ft_strlen(tab[0]) - 1] == ':')
	{
		if (asm_error_label(app, tab[0]))
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

void		asm_check_cmd(t_app *app, char **tab)
{
	int		i;

	i = 0;
	if (tab[0] && asm_check_label(app, tab[0]))
		i = 1;
	else if (tab[0] && asm_is_instr(app, tab[0]))
		i = 0;
	else
		asm_put_error("Error : No label or instruction");
	if (!asm_is_instr(app, tab[i]))
	{
		if (!tab[i])
			return ;
		else
			asm_put_error("Error : No valid instruction after label");
	}
	asm_set_cmd(app, tab, i);
}
