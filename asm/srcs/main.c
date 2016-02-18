#include "asm.h"

void	asm_init_app(t_app *app)
{
	app->fd = -1;
	app->ret = -1;
	app->lst_line = NULL;
	app->label = NULL;
	app->waiting_label = NULL;
	app->btcode = NULL;
	ft_bzero(&app->header, sizeof(app->header));
	app->cursor = asm_create_cursor();
	asm_init_instr(app);
	int 	i = 0;
	while (i < 16)
	{
		printf("[name : %5s] [opcode : %#4x] [is_encoding : %d] [",
			app->instr[i].name, app->instr[i].opcode, app->instr[i].is_encoding);
		int j = 0;
		while (j < 4)
		{
			printf("%2d ", app->instr[i].nbr_octet[j]);
			j++;
		}
		printf("]\n");
		i++;
	}
}

int 	asm_is_label(t_app *app, char *str)
{
	t_label		*l;

	l = app->label;
	while (l)
	{
		if (ft_strcmp(l->name, str) == 0)
			return (1);
		l = l->next;
	}
	return (0);
}

int 	asm_is_instr(t_app *app, char *str)
{
	int 	i;

	i = 0;
	while (i < 16)
	{
		if (ft_strcmp(app->instr[i].name, str) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	asm_check_btcode(t_app *app, char **tab)
{
	int 	i;

	i = 0;
	if (tab[0] && asm_is_label(app, tab[0]))
		i = 1;
	else if (tab[0] && asm_is_instr(app, tab[0]))
		i = 0;
	else
		asm_put_error("Error : No label or instruction");
	if (!asm_is_instr(app, tab[i]))
	{
		if (!tab[i]) // si la ligne ne contient qu'un label
		{
			if (app->waiting_label == NULL)
			{
				app->waiting_label = tab[0];
				return ;
			}
			else
				asm_put_error("Error : Multiple labels");
		}
		else
			asm_put_error("Error : No valid instruction after label");
	}
	if (app->waiting_label)
	{
		// TODO set label to current line in /!\ BTCODE /!\
		// asm_set_label(app->waiting_label, ?);
		app->waiting_label = NULL;
	}
	// TODO set instruction to command line
	//	asm_set_instr(app, tab[i]);
	// TODO set args to cmd
	//	asm_set_arg(app, tab[i + 1]);
}

void	asm_save_btcode(t_app *app)
{
	t_node		*l;
	char		**tab;

	l = app->lst_line;
	while (l && l->n_line < 3)
		l = l->next;
	while (l)
	{
		tab = asm_strsplit(l->line);
		if (tab[0] && tab[0][0] != '\n')
			asm_check_btcode(app, tab);
		l = l->next;
	}
}

void	asm_set_encoding_byte(t_cmd *cmd)
{
	int 			i;
	unsigned char	mask_dir;
	unsigned char	mask_ind;
	unsigned char	mask_reg;

	i = 0;
	cmd->encoding = 0x00;
	if (cmd->instr.is_encoding)
	{
		mask_dir = 0x80;
		mask_ind = 0xc0;
		mask_reg = 0x40;
		while (i < 4)
		{
			if (cmd->param[i].size == 4)
				cmd->encoding |= (mask_dir >> i * 2);
			else if (cmd->param[i].size == 2)
				cmd->encoding |= (mask_ind >> i * 2);
			else if (cmd->param[i].size == 1)
				cmd->encoding |= (mask_reg >> i * 2);
			else
				cmd |= (0x00 >> i * 2);
			i++;
		}
	}
}

void	asm_set_bytecode(t_app *app)
{
	t_btcode	*btcode;

	btcode = app->btcode;
	while (btcode)
	{
		asm_set_encoding_byte(btcode->cmd);
		btcode = btcode->next;
	}
}

int		main(int ac, char **av)
{
	t_app app;

	if (ac != 2)
		asm_put_error("Error : Bad argc number");
	asm_init_app(&app);
	asm_check_extension(&app, av);
	asm_open_file(&app, av);
	asm_read_file(&app);
	//asm_parse(&app);

	// Debug
	//ft_putstr("Nom du programme : ");
	//ft_putstr(app.header.prog_name);
	//ft_putchar('\n');

	asm_save_label(&app);
	asm_save_btcode(&app);
	asm_set_bytecode(&app);
	// TODO asm_parse_btcode(&app);
	// TODO	asm_write_file(&app);
	return (0);
}
