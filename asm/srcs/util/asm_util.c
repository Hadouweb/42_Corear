/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlouise <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 11:37:41 by dlouise           #+#    #+#             */
/*   Updated: 2016/02/21 21:30:55 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			asm_check_extension(t_app *app, char **av)
{
	int len;

	len = ft_strlen(av[1]);
	if (len < 2 || av[1][len - 1] != 's' || av[1][len - 2] != '.')
		asm_put_error("Error : Bad file type");
	app = (void*)app;
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

void			asm_delete_comment_after_header(t_app *app)
{
	t_node			*line;
	unsigned int	num_line;
	unsigned int	num_col;

	num_line = 1;
	line = app->lst_line;
	while (line)
	{
		num_col = 0;
		while (line->line[num_col])
		{
			if (num_line >= app->cursor->line
					&& (line->line[num_col] == '#'
						|| line->line[num_col] == ';'))
				line->line[num_col] = '\0';
			num_col++;
		}
		num_line++;
		line = line->next;
	}
}
