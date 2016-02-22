/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atrupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 02:46:43 by atrupin           #+#    #+#             */
/*   Updated: 2016/02/21 23:40:08 by mfroehly         ###   ########.fr       */
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
	char			*line;
	struct s_node	*next;
	int				n_line;
}					t_node;

typedef struct		s_label
{
	char			*name;
	int				pos;
	struct s_label	*next;
}					t_label;

typedef struct		s_size_p
{
	int				a;
	int				b;
	int				c;
	int				d;
}					t_size_p;

typedef struct		s_instr
{
	char			*name;
	unsigned char	opcode;
	int				nbr_octet[4];
	unsigned char	type_param[4];
	int				is_encoding;
}					t_instr;

typedef struct		s_param
{
	char			*str;
	int				size;
	unsigned int	hex;
}					t_param;

typedef struct		s_cmd
{
	struct s_instr	instr;
	unsigned char	encoding;
	struct s_param	param[4];
	int				cmd_size;
}					t_cmd;

typedef struct		s_btcode
{
	int				size_hex;
	struct s_cmd	*cmd;
	unsigned int	n_line;
	struct s_btcode	*next;
}					t_btcode;

typedef	struct		s_app
{
	int				fd;
	int				ret;
	t_node			*lst_line;
	t_label			*label;
	t_header		header;
	t_cursor		*cursor;
	t_btcode		*btcode;
	const t_instr	*instr;
	unsigned int	byte_count;
	char			*path_out_file;
}					t_app;

/*
** init/asm_init_instr.c
*/
void				asm_init_instr(t_app *app);

/*
** parsing/asm_check_cmd.c
*/
int					asm_is_label(t_app *app, char *str);
int					asm_is_instr(t_app *app, char *str);
int					asm_check_label(t_app *app, char *str);
void				asm_check_cmd(t_app *app, char **tab, int line);

/*
** parsing/asm_join_arg.c
*/
void				asm_join_arg(t_app *app, char **tab, int i);

/*
** parsing/asm_parse_cmd.c
*/
void				asm_set_cmd(t_app *app, char **tab, int i);

/*
** parsing/asm_parse_header.c
*/
int					asm_read_directive(t_app *app);

/*
** parsing/asm_parsing.c
*/
void				asm_parse_header(t_app *app);
void				asm_save_cmd(t_app *app);
void				asm_parse(t_app *app);

/*
** read/asm_file.c
*/
void				asm_read_file(t_app *app, char *name);

/*
** util/asm_strsplit.c
*/
char				**asm_strsplit(char const *s);

/*
** util/asm_push_data.c
*/
t_btcode			*asm_create_bt(void);
void				asm_push_bt(t_app *app, t_btcode *btcode);
void				asm_push_label(t_app *app, char *str);

/*
** util/asm_error.c
*/
void				asm_put_error(char *str);
void				asm_put_error_line(char *str, int line);
void				asm_put_error_str(char *str1, char *str2);
void				asm_put_error_char_int_int(char *str, char c, int line,
						int col);
void				asm_put_error_str_int_int(char *str1, char *str2,
						int line, int col);

/*
** util/asm_success.c
*/
void				asm_put_success(char *str1, char *str2);

/*
** util/asm_debug.c
*/
void				asm_debug_instr_init(t_app app);
void				asm_debug_label(t_app app);
void				asm_debug_btcode(t_app app);

/*
** util/asm_cursor.c
*/
t_cursor			*asm_create_cursor();
char				*asm_get_line(t_app *app, unsigned int n);
char				asm_get_char(char *line, unsigned int n);
char				asm_read_char(t_app *app);

/*
** util/asm_util.c
*/
void				asm_check_extension(t_app *app, char **av);
int					asm_isalnum(char *str);
void				asm_free_tab(char **tab);
unsigned int		asm_reverse_uint(unsigned int n);
void				asm_delete_comment_after_header(t_app *app);

/*
** write/asm_write.c
*/
void				asm_open_out_file(t_app *app, char **av);
void				asm_write_data(t_app *app);

void				asm_init_type_param(t_app *app);

void				asm_check_line(t_app *app, char *str, int line);
int					asm_error_instr(char **str, t_app *app, int line, t_btcode *bt);
void				asm_error_label(char **str, t_app *app);
void				asm_error_param(char **str, int line, t_btcode *btcode);
t_instr				asm_get_instr(t_app *app, int i_instr);

void				asm_set_cmd_instr(t_app *app, t_btcode *bt, int i_instr);
void				asm_set_cmd_param(t_btcode *bt, char *str, int i);
void				asm_set_encoding_byte(t_cmd *cmd);

#endif
