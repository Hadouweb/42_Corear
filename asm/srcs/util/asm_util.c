#include "asm.h"

void	asm_check_extension(t_app *app, char **av)
{
	int len;

	len = ft_strlen(av[1]);
	if (len < 2 || av[1][len - 1] != 's' || av[1][len - 2] != '.')
		asm_put_error("Error : Bad file type");
	app = (void*)app;
}

void	asm_put_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
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

int		asm_isalnum(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != ':')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			i++;
		else if (str[i] == '_')
			i++;
		else if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}
