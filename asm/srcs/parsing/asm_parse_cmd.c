#include "asm.h"

void	asm_set_cmd_param(t_btcode *bt, char *str)
{
	char	**tab;
	int		i;
	int		s;

	tab = ft_strsplit(str, ',');
	i = 0;
	while (tab[i])
	{
		bt->cmd->param[i].str = ft_strdup(tab[i]);
		if (tab[i][0] == '%')
			s = 4;
		else if (tab[i][0] == 'r')
			s = 1;
		else
			s = 2;
		bt->cmd->param[i].size = s;
		bt->cmd->param[i].hex = 0;
		i++;
	}
	asm_free_tab(tab);
}

void	asm_set_real_param_size(t_cmd *cmd)
{
	int		i;
	int		s;

	i = 0;
	s = 0;
	while (i < 4)
	{
		s = 0;
		if (cmd->param[i].str)
		{
			if (cmd->param[i].str[0] == '%')
				s = (cmd->param[i].str[1] == ':') ? 2 : 4;
			else if (cmd->param[i].str[0] == 'r')
				s = 1;
			else
				s = 2;
		}
		if (s <= cmd->instr.nbr_octet[i])
			cmd->param[i].size = s;
		else if (cmd->instr.nbr_octet[i] < s)
			cmd->param[i].size = cmd->instr.nbr_octet[i];
		cmd->cmd_size += cmd->param[i].size;
		i++;
	}
}

void	asm_set_cmd_instr(t_app *app, t_btcode *bt, char *str)
{
	int		i;
	t_cmd	*c;

	if ((c = (t_cmd *)ft_memalloc(sizeof(t_cmd))) == NULL)
		asm_put_error("Error : Malloc CMD");
	bt->cmd = c;
	i = 0;
	bt->cmd->cmd_size = 1;
	while (i < 16)
	{
		if (ft_strcmp(app->instr[i].name, str) == 0)
		{
			bt->cmd->instr.name = app->instr[i].name;
			bt->cmd->instr.opcode = app->instr[i].opcode;
			bt->cmd->instr.nbr_octet[0] = app->instr[i].nbr_octet[0];
			bt->cmd->instr.nbr_octet[1] = app->instr[i].nbr_octet[1];
			bt->cmd->instr.nbr_octet[2] = app->instr[i].nbr_octet[2];
			bt->cmd->instr.nbr_octet[3] = app->instr[i].nbr_octet[3];
			bt->cmd->instr.is_encoding = app->instr[i].is_encoding;
			bt->cmd->cmd_size += bt->cmd->instr.is_encoding;
			return ;
		}
		i++;
	}
	asm_put_error("Error : No valid instruction");
}

void	asm_set_encoding_byte(t_cmd *cmd)
{
	int				i;
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
			i++;
		}
	}
}

void	asm_set_cmd(t_app *app, char **tab, int i)
{
	t_btcode	*bt;
	t_label		*l;

	bt = asm_create_bt();
	l = app->label;
	while (l)
	{
		if (l->pos == -1)
			l->pos = app->byte_count;
		l = l->next;
	}
	asm_set_cmd_instr(app, bt, tab[i]);
	asm_set_cmd_param(bt, tab[i + 1]);
	asm_set_encoding_byte(bt->cmd);
	asm_set_real_param_size(bt->cmd);
	asm_push_bt(app, bt);
	app->byte_count += bt->cmd->cmd_size;
}
