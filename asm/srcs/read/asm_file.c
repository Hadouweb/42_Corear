#include "asm.h"

static t_node	*asm_create_line(char *str, int i)
{
	t_node	*n;

	if ((n = (t_node*)ft_memalloc(sizeof(t_node))) == NULL)
		asm_put_error("Error : Node not created");
	n->next = NULL;
	n->line = str;
	n->n_line = i;
	return (n);
}

void			asm_push_line(t_app *app, char *str, int i)
{
	t_node	*l;

	l = app->lst_line;
	if (l)
	{
		while (l->next)
			l = l->next;
		l->next = asm_create_line(str, i);
	}
	else
		app->lst_line = asm_create_line(str, i);
}

void			asm_read_file(t_app *app, char *name)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if ((app->fd = open(name, O_RDONLY)) == -1)
		asm_put_error("Error : Can't open the file");
	while ((app->ret = get_next_line(app->fd, &line)) > 0)
	{
		j = 0;
		while (line[j])
		{
			if (line[j] == '#' || line[j] == ';')
				line[j] = '\0';
			j++;
		}
		asm_push_line(app, line, i);
		i++;
	}
	if (app->ret == -1)
		asm_put_error("Error : An error occured while reading the file");
	close(app->fd);
}
