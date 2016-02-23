/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlouise <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 11:32:59 by dlouise           #+#    #+#             */
/*   Updated: 2016/02/21 23:08:39 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			main(int ac, char **av)
{
	t_app app;

	if (ac != 2)
		asm_put_error("Error : Bad argc number");
	asm_init_app(&app);
	asm_check_extension(&app, av);
	asm_read_file(&app, av[1]);
	asm_parse(&app);
	asm_open_out_file(&app, av);
	asm_write_data(&app);
	//asm_debug_btcode(app);
	//asm_debug_label(app);
	//sleep(10);
	return (0);
}
