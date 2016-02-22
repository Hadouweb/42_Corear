#include "asm.h"

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

int		asm_syntax_param(char **str, int line, t_btcode *btcode, int j)
{
	char	*tmp;
	int		i;
	int		token;

	tmp = *str;
	token = 0;
	i = asm_syntax2_param(*str, tmp, line);
	while (tmp[i] && ft_isalnum(tmp[i]))
		i++;
	asm_set_cmd_param(btcode, ft_strndup(*str, i), j);
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
	return (i);
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

void	asm_error_param(char **str, int line, t_btcode *btcode)
{
	int		i;
	int		next_param;
	char	*tmp;
	t_instr	instr;

	tmp = *str;
	instr = btcode->cmd->instr;
	i = 0;
	next_param = 0;
	while (instr.type_param[i])
	{
		if (asm_format_param(tmp, instr.type_param[i]))
		{
			next_param = asm_syntax_param(str, line, btcode, i);
			*str += next_param;
		}
		else
			asm_put_error_line(instr.name, line);
		i++;
	}
	asm_set_encoding_byte(btcode->cmd);
}