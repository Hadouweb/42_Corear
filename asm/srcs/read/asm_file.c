#include "asm.h"

void	asm_open_file(t_app *app, char **av)
{
	if ((app->fd = open(av[1], O_RDONLY)) == -1)
		asm_put_error("Error : Can't open the file");
}

void	asm_read_file(t_app *app)
{
	char 	*line;
	int 	i;

	i = 0;
	while ((app->ret = get_next_line(app->fd, &line)) > 0)
	{
		asm_push_line(app, line, i);
		i++;
	}
	if (app->ret == -1)
		asm_put_error("Error : An error occured while reading the file");
	close(app->fd);

}

static t_node	*asm_create_line(char *str, int i)
{
	t_node	*n;

	if ((n = (t_node*)malloc(sizeof(t_node))) == NULL)
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