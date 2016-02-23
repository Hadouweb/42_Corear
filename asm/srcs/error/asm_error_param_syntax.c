/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_error_param_syntax.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 07:26:00 by nle-bret          #+#    #+#             */
/*   Updated: 2016/02/23 07:26:04 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_syntax_param_reg(char *str, int line)
{
	int		i;

	i = 0;
	if (str[i] && str[i] == 'r')
	{
		i++;
		while (str[i] && (ft_isdigit(str[i])))
			i++;
		return (i);
	}
	else
		asm_put_error_line(str, line);
	return (0);
}

int		asm_syntax_param_dir(char *str, int line)
{
	int		i;

	i = 0;
	if (str[i] && str[i] == '%')
	{
		i++;
		if (str[i] && str[i] == ':')
		{
			i++;
			if (!asm_is_label_char(str[i]))
				asm_put_error_line(str, line);
		}
		else if (str[i] && asm_param_is_number(&str[i]))
		{
			if (str[i] == '-')
			{
				i++;
				if (!str[i] || !ft_isdigit(str[i]))
					asm_put_error_line(str, line);
			}
			else if (!ft_isdigit(str[i]))
				asm_put_error_line(str, line);
		}
	}
	else
		asm_put_error_line(str, line);
	while (asm_is_label_char(str[i]))
		i++;
	return (i);
}

int		asm_syntax_param_ind(char *str, int line)
{
	int		i;

	i = 0;
	if (*str)
	{
		if (str[0] == '-')
		{
			i++;
			if (!str[i] || !ft_isdigit(str[i]))
				asm_put_error_line(str, line);
		}
		else if (!ft_isdigit(str[i]))
			asm_put_error_line(str, line);
	}
	else
		asm_put_error_line(str, line);
	while (str[i] && (ft_isdigit(str[i])))
		i++;
	return (i);
}

int		asm_syntax_param(char **str, t_btcode *btcode, int j, int f)
{
	char	*tmp;
	int		i;
	int		token;

	tmp = *str;
	token = 0;
	i = 0;
	if (f == 1)
		i = asm_syntax_param_reg(tmp, btcode->n_line);
	else if (f == 2)
		i = asm_syntax_param_dir(tmp, btcode->n_line);
	else if (f == 4)
		i = asm_syntax_param_ind(tmp, btcode->n_line);
	asm_set_cmd_param(btcode, ft_strndup(*str, i), j);
	i += asm_dodge_space_tab(&tmp[i]);
	if (tmp[i] != ',' && tmp[i] != '\0')
		asm_put_error_line(*str, btcode->n_line);
	if (tmp[i] == ',' && ++token)
		i++;
	i += asm_dodge_space_tab(&tmp[i]);
	if (token && tmp[i] == '\0')
		asm_put_error_line("ENDLINE", btcode->n_line);
	return (i);
}
