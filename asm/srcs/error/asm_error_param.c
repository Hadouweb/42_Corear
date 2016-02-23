/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error_param.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 07:25:52 by nle-bret          #+#    #+#             */
/*   Updated: 2016/02/23 07:25:54 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_format_param(char *str, unsigned char format)
{
	if (*str)
	{
		if (format & 0x01)
			if (str[0] == 'r')
				return (1);
		if (format & 0x02)
			if (str[0] == '%')
				return (2);
		if (format & 0x04)
			if (asm_param_is_number(&str[0]))
				return (4);
	}
	return (0);
}

void	asm_error_param(char **str, int line, t_btcode *btcode)
{
	int		i;
	int		next_param;
	char	*tmp;
	t_instr	instr;
	int		f;

	tmp = *str;
	instr = btcode->cmd->instr;
	i = 0;
	next_param = 0;
	while (instr.type_param[i])
	{
		if ((f = asm_format_param(*str, instr.type_param[i])) > 0)
		{
			next_param = asm_syntax_param(str, btcode, i, f);
			*str += next_param;
		}
		else
			asm_put_error_line(*str, line);
		i++;
	}
	asm_set_encoding_byte(btcode->cmd);
	asm_set_param_hex(btcode->cmd);
}
