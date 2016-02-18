#include "asm.h"

void	asm_check_extension(t_app *app, char **av)
{
	int len;

	len = ft_strlen(av[1]);
	if (len < 2 || av[1][len - 1] != 's' || av[1][len - 2] != '.')
		asm_put_error("Error : Bad file type");

	app = (void*)app;
}

void	asm_put_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

