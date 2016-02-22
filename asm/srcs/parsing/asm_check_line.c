#include "asm.h"

int		asm_is_label_char(char c)
{
	int			i;
	const char	lb[] = LABEL_CHARS;

	i = 0;
	while (lb[i])
	{
		if (c == lb[i])
			return (1);
		i++;
	}
	return (0);
}


void	asm_error_label(char **str)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = *str;
	while (asm_is_label_char(tmp[i]))
		i++;
	if (tmp[i] == ':')
	{
		i++;
		while (tmp[i] == ' ' || tmp[i] == '\t')
			i++;
		*str += i;
	}
}

char	*asm_strndup(char *str, int len)
{
	char	*rep;

	if ((rep = (char*)ft_memalloc(len + 1)) == NULL)
		asm_put_error("Error : Malloc");
	ft_strncpy(rep, str, len);
	rep[len] = '\0';
	return (rep);
}

int		asm_error_instr_exist(t_app *app, char *instr, int line)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(app->instr[i].name, instr) == 0)
			return (i);
		i++;
	}
	asm_put_error_line(instr, line);
	return (i);
}

int		asm_error_instr(char **str, t_app *app, int line)
{
	int				i;
	char			*tmp;
	char			*tmp_instr;
	int				index_instr;

	i = 0;
	tmp = *str;
	tmp_instr = NULL;
	index_instr = 0;
	while (tmp[i] && tmp[i] != ' ' && tmp[i] != '\t' && tmp[i] != '%')
		i++;
	tmp_instr = asm_strndup(*str, i);
	index_instr = asm_error_instr_exist(app, tmp_instr, line);
	while (tmp[i] == ' ' || tmp[i] == '\t')
		i++;
	*str += i;
	ft_strdel(&tmp_instr);
	return (index_instr);
}

t_instr	asm_get_instr(t_app *app, int i_instr)
{
	int		i;

	i = 0;
	while (i < 16 && i != i_instr)
		i++;
	return (app->instr[i]);
}

int		asm_syntax2_param(char *str, char *tmp, int line)
{
	int		i;

	i = 0;
	if (tmp[0] == '%')
	{
		i++;
		if (tmp[1] == ':')
		{
			if (!ft_isalnum(tmp[2]))
				asm_put_error_line(str, line);
			i++;
		}
		else if (!ft_isalnum(tmp[1]))
			asm_put_error_line(str, line);
	}
	else if (tmp[0] == 'r')
	{
		if (!ft_isdigit(tmp[1]))
			asm_put_error_line(str, line);
	}
	else
		asm_put_error_line(str, line);
	return (i);
}

void	asm_syntax_param(char **str, int line)
{
	char	*tmp;
	int		i;
	int		token;

	tmp = *str;
	token = 0;
	i = asm_syntax2_param(*str, tmp, line);
	while (tmp[i] && ft_isalnum(tmp[i]))
		i++;
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	if (tmp[i] != ',' && tmp[i] != '\0')
		asm_put_error_line(*str, line);
	if (tmp[i] == ',' && ++token)
		i++;
	while (tmp[i] && (tmp[i] == ' ' || tmp[i] == '\t'))
		i++;
	if (token && tmp[i] == '\0')
		asm_put_error_line("ENDLINE", line);
	*str += i;
}

int		asm_format_param(char *str, unsigned char format)
{
	if (str)
	{
		if (format & 0x01)
			if (str[0] == 'r')
				return (1);
		if (format & 0x02)
			if (str[0] == '%')
				return (1);
		if (format & 0x04)
			if (ft_isdigit(str[0]))
				return (1);
	}
	return (0);
}

void	asm_error_param(char **str, t_app *app, int line, int i_instr)
{
	int		i;
	char	*tmp;
	t_instr	instr;

	tmp = *str;
	instr = asm_get_instr(app, i_instr);
	i = 0;
	while (instr.type_param[i])
	{
		if (asm_format_param(tmp, instr.type_param[i]))
			asm_syntax_param(str, line);
		else
			asm_put_error_line(instr.name, line);
		i++;
	}
}

void	asm_check_line(t_app *app, char *str, int line)
{
	int		i;
	int		index_instr;

	i = 0;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str)
	{
		asm_error_label(&str);
		index_instr = asm_error_instr(&str, app, line);
		asm_error_param(&str, app, line, index_instr);
		//printf("[%s] %d\n", str, line);
		if (*str)
			asm_put_error_line(str, line);
	}
}