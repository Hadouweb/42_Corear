#include "asm.h"

void	asm_init_app(t_app *app)
{
	app->byte_count = 0;
	app->fd = -1;
	app->ret = -1;
	app->lst_line = NULL;
	app->label = NULL;
	app->btcode = NULL;
	ft_bzero(&app->header, sizeof(app->header));
	app->cursor = asm_create_cursor();
	asm_init_instr(app);
}

int		main(int ac, char **av)
{
	t_app app;

	if (ac != 2)
		asm_put_error("Error : Bad argc number");
	asm_init_app(&app);
	asm_check_extension(&app, av);
	asm_read_file(&app, av[1]);
	asm_parse(&app);
	asm_write_data(&app);
	return (0);
}
