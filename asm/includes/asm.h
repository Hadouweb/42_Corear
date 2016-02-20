/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 02:46:43 by atrupin           #+#    #+#             */
/*   Updated: 2016/02/19 09:08:20 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include <stdlib.h>
# include <libft.h>
# include <fcntl.h>
# include "op.h"
# include <stdio.h>

typedef struct		s_cursor
{
	unsigned int	line;
	unsigned int	col;
}					t_cursor;

typedef struct		s_node
{
	char 			*line;
	struct s_node 	*next;
	int 			n_line;
}					t_node;

typedef struct  	s_label
{
	char			*name;
	int 			pos;
	struct s_label	*next;
}					t_label;

typedef struct 		s_size_p
{
	int 			a;
	int 			b;
	int 			c;
	int 			d;
}					t_size_p;

typedef struct 		s_instr
{
	char 			*name;
	unsigned char 	opcode;
	int 			nbr_octet[4];
	int 			is_encoding;
}					t_instr;

typedef struct 		s_param
{
	char 			*str;
	int 			size;
	unsigned int 	hex;
}					t_param;

typedef struct  	s_cmd
{
	struct s_instr	instr;
	unsigned char 	encoding;
	struct s_param	param[4];
	int 			cmd_size;
}					t_cmd;

typedef struct 		s_btcode
{
	int 			size_hex;
	struct s_cmd 	*cmd;
	struct s_btcode	*next;
}					t_btcode;

typedef	struct		s_app
{
	int				fd;
	int				ret;
	t_node			*lst_line;
	t_label			*label;
	header_t		header;
	t_cursor		*cursor;
	t_btcode 		*btcode;
	struct s_instr	instr[16];
	int 			byte_count;
}					t_app;

void				asm_put_error(char *str);
void				asm_push_line(t_app *app, char *line, int i);
void				asm_check_extension(t_app *app, char **av);
void				asm_read_file(t_app *app, char *name);
t_cursor			*asm_create_cursor();
char				*asm_get_line(t_app *app, unsigned int n);
char				asm_get_char(char *line, unsigned int n);
char				asm_read_char(t_app *app);
void				asm_init_app(t_app *app);

void				asm_parse(t_app *app);

char				**asm_strsplit(char const *s);

void				asm_push_label(t_app *app, char *str);
void				asm_save_label(t_app *app);

int					asm_isalnum(char *str);
void				asm_init_instr(t_app *app);

int 				asm_is_label(t_app *app, char *str);
int 				asm_is_instr(t_app *app, char *str);
void				asm_check_cmd(t_app *app, char **tab);
void				asm_save_cmd(t_app *app);

void				asm_push_cmd(t_app *app, t_btcode *to_push);
t_btcode			*asm_create_cmd(void);
void				asm_set_cmd(t_app *app, char **tab, int i);

void				asm_debug_instr_init(t_app app);
void				asm_debug_btcode(t_app app);

void				asm_set_encoding_byte(t_cmd *cmd);
void				asm_debug_label(t_app app);

void				asm_write_data(t_app *app);
void				asm_pass_comment(t_app *app);
void				asm_read_directive_value(t_app *app, char *dst_value, int length);
void				asm_parse_header(t_app *app);

t_btcode			*asm_create_bt(void);
void				asm_push_bt(t_app *app, t_btcode *bt);
void				asm_push_label(t_app *app, char *str);
int					asm_read_directive(t_app *app);

#endif
