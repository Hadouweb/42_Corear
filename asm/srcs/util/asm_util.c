#include "asm.h"

void			asm_check_extension(t_app *app, char **av)
{
	int len;

	len = ft_strlen(av[1]);
	if (len < 2 || av[1][len - 1] != 's' || av[1][len - 2] != '.')
		asm_put_error("Error : Bad file type");
	app = (void*)app;
}

void			asm_put_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

int				asm_isalnum(char *str)
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

void			asm_free_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

unsigned int	asm_reverse_uint(unsigned int n)
{
	unsigned char	*t;

	t = (unsigned char*)&n;
	return (0
		| (unsigned int)t[0] << 24
		| (unsigned int)t[1] << 16
		| (unsigned int)t[2] << 8
		| (unsigned int)t[3]);
}
