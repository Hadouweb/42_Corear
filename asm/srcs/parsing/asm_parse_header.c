#include "asm.h"

void	asm_read_directive_value(t_app *app, char *dst_value, int length)
{
	int		i;
	char	c;

	while (1)
	{
		c = asm_read_char(app);
		if (c == ' ' || c == '\t')
			continue ;
		if (c != '"')
			asm_put_error(
				"Error : directive value must begin with a quotation mark");
		break ;
	}
	c = asm_read_char(app);
	i = 0;
	while (c != '"' && i < length)
	{
		dst_value[i] = c;
		i++;
		c = asm_read_char(app);
	}
	if (c != '"')
		asm_put_error("Error : directive value is too long");
}

void	asm_read_directive_name(t_app *app, char directive[8])
{
	int		i;

	i = 0;
	directive[i] = asm_read_char(app);
	while (directive[i] != ' ' && directive[i] != '\t' && i < 7)
	{
		i++;
		directive[i] = asm_read_char(app);
	}
	if ((directive[i] != ' ' && directive[i] != '\t')
		|| (ft_strncmp(directive, "name", 4) != 0
			&& (ft_strncmp(directive, "comment", 7) != 0)))
		asm_put_error("Error : directive not expected");
	directive[i] = '\0';
}

void	asm_check_after_directive(t_app *app)
{
	char	c;

	c = asm_read_char(app);
	while (c == ' ' || c == '\t')
		c = asm_read_char(app);
	if (c == ';' || c == '#')
	{
		c = asm_read_char(app);
		while (c != '\n')
			c = asm_read_char(app);
	}
	if (c != '\n')
		asm_put_error("Error : unexpected character after the directive");
}

int		asm_read_directive(t_app *app)
{
	char		directive_name[8];
	static	int nb_directive = 0;

	if (nb_directive++ == 2)
		asm_put_error("Error : too directives");
	asm_read_directive_name(app, directive_name);
	if (ft_strcmp(directive_name, "name") == 0)
		asm_read_directive_value(app, app->header.prog_name, PROG_NAME_LENGTH);
	if (ft_strcmp(directive_name, "comment") == 0)
		asm_read_directive_value(app, app->header.comment, COMMENT_LENGTH);
	asm_check_after_directive(app);
	if (*app->header.prog_name && *app->header.comment)
		return (1);
	return (0);
}
