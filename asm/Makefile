CC = gcc -Werror -Wextra -Wall

SRCPATH = ./srcs
PARSINGPATH = $(SRCPATH)/parsing
READPATH = $(SRCPATH)/read
UTILPATH = $(SRCPATH)/util
INITPATH = $(SRCPATH)/init

INCPATH = ./includes

LIBFT = ./libft

HEADER = -I $(LIBFT)/includes -I $(INCPATH)

LIB = $(LIBFT)/libft.a 

SRC = $(SRCPATH)/main.c\
	  $(UTILPATH)/asm_util.c\
	  $(UTILPATH)/asm_cursor.c\
	  $(UTILPATH)/asm_strsplit.c\
	  $(READPATH)/asm_file.c\
	  $(PARSINGPATH)/asm_parse_label.c\
	  $(PARSINGPATH)/asm_parsing.c\
	  $(INITPATH)/asm_init_instr.c

OBJ = $(SRC:.c=.o)

NAME = asm

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C $(LIBFT)
	@$(CC) $(HEADER) $(LIB) -o $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(HEADER) -o $@ -c $<
	@echo "\033[33m█\033[0m\c"

clean : 
	@make -C $(LIBFT) clean
	rm -rf $(OBJ)

fclean : clean
	@make -C $(LIBFT) fclean
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
