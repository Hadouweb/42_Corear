#include "libft.h"
#include "asm.h"

void	asm_parse_header(t_app *app)
{
/*	char	*begin;
	char	*end;
	char	*middle;
	char	*dst;
	char	*src;

	if (ft_strncmp(app->lst_line->line, ".name", 5))
		asm_put_error("Error : .name missing");
	begin = &app->lst_line->line[5];
	while(*begin == ' ' || *begin == '\t')
		begin++;
	if (*begin != '"')
		asm_put_error("Error : not expected character after .name");
	begin++;
	end = begin;
	while (*end)
		end++;
	while(*end == '\0' || *end == ' ' || *end == '\t')
		end--;
	if (*end != '"')
		asm_put_error("Error : quote not found at the end of .name");
	end--;
	middle = begin;
	while (middle <= end)
	{
		if (*middle == '"' && *(middle-1) != '\\')
			asm_put_error("Error : quote not escape on .name");
		middle++;
	}
	if ((middle - end) + 1 > PROG_NAME_LENGTH) // TODO : Ne tient pas compte des echapements
		asm_put_error("Error : .name too long");
	dst = app->header.prog_name;
	src = begin;
	while (src <= end)
	{
		if (*src == '\\')
			src++;
		*dst = *src;
		src++;
		dst++;
	}*/

	ft_putstr("source:");
	char c;
	while ((c = asm_read_char(app)) != '\0')
		ft_putchar(c);
}

void	asm_parse(t_app *app)
{
	asm_parse_header(app);
}
