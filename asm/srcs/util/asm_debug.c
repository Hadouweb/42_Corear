/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlouise <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/21 11:37:26 by dlouise           #+#    #+#             */
/*   Updated: 2016/02/21 11:38:14 by dlouise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	asm_debug_instr_init(t_app app)
{
	int 	i = 0;
	while (i < 16)
	{
		printf("[name : %5s] [opcode : %#4x] [is_encoding : %d] [",
			app.instr[i].name, app.instr[i].opcode, app.instr[i].is_encoding);
		int j = 0;
		while (j < 4)
		{
			printf("%2d ", app.instr[i].nbr_octet[j]);
			j++;
		}
		printf("]\n");
		i++;
	}
}

void	asm_debug_label(t_app app)
{
	t_label	*l;

	l = app.label;
	printf("___________________________________________\nLabel\n");
	while (l)
	{
		printf("\033[32mname :\t\033[0m %s\n", l->name);
		printf("\033[33mpos :\t\033[0m %d\n\n", l->pos);
		l = l->next;
	}
}

void	asm_debug_btcode(t_app app)
{
	t_btcode	*bt;
	int 		i;

	bt = app.btcode;
	printf("DEBUG\n\n");
	while (bt)
	{
		i = 0;
		//printf("\033[35mLine (Hexa) :\t\t\t\033[0m %s\n", bt->line);
			printf("\t\033[32mCmd : \n");
				printf("\t\t\033[33mInstr :\t\t\033[0m %s\n", bt->cmd->instr.name);
				printf("\t\t\033[33mOpcode :\t\033[0m %#x\n", bt->cmd->instr.opcode);
				printf("\t\t\033[33mNbr octet :\t\033[0m ");
			while (i < 4)
			{
				printf("%d ", bt->cmd->instr.nbr_octet[i]);
				i++;
			}
			printf("\n\t\t\033[33mIs encoding :\t\033[0m %d\n", bt->cmd->instr.is_encoding);
			printf("\t\t\033[33mFull cmd size :\t\033[0m %d\n", bt->cmd->cmd_size);
			printf("\n\t\t\033[36mEncodage :\t\t\033[0m %#x\n", bt->cmd->encoding);
			printf("\n\t\t\033[36mParam :\t\t\033[0m \n");
			i = 0;
			while (i < 4)
			{
				printf("\t\t\t%8s ", bt->cmd->param[i].str);
				printf("\t%2d ", bt->cmd->param[i].size);
				printf("\t%#x\n ", bt->cmd->param[i].hex);
				i++;
			}
		printf("\n___________________________________________________________________\n");
		bt = bt->next;
	}

}
