CC = gcc -Werror -Wextra -Wall

SRCPATH = ./srcs
PARSINGPATH = $(SRCPATH)/parsing
READPATH = $(SRCPATH)/read
UTILPATH = $(SRCPATH)/util
INITPATH = $(SRCPATH)/init
WRITEPATH = $(SRCPATH)/write
ERRORPATH = $(SRCPATH)/_error
BTCODEPATH = $(SRCPATH)/_set_btcode

INCPATH = ./includes

LIBFT = ./libft

HEADER = -I $(LIBFT)/includes -I $(INCPATH)

LIB = $(LIBFT)/libft.a 

SRC = $(SRCPATH)/main.c\
	  $(UTILPATH)/asm_util.c\
	  $(UTILPATH)/asm_cursor.c\
	  $(UTILPATH)/asm_strsplit.c\
	  $(UTILPATH)/asm_debug.c\
	  $(UTILPATH)/asm_push_data.c\
	  $(UTILPATH)/asm_error.c\
	  $(UTILPATH)/asm_success.c\
	  $(READPATH)/asm_file.c\
	  $(PARSINGPATH)/asm_parsing.c\
	  $(PARSINGPATH)/asm_parse_header.c\
	  $(INITPATH)/asm_init_instr.c\
	  $(WRITEPATH)/asm_write.c\
	  $(ERRORPATH)/asm_error.c\
	  $(ERRORPATH)/asm_error_instr.c\
	  $(ERRORPATH)/asm_error_label.c\
	  $(ERRORPATH)/asm_error_param.c\
	  $(BTCODEPATH)/asm_set_btcode.c\

OBJ = $(SRC:.c=.o)

NAME = asm

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C $(LIBFT)
	@$(CC) $(HEADER) $(LIB) -o $(NAME) $(OBJ)
	@echo " "
	@echo "   \033[33m                                         \033[043m        \033[0m"
	@echo "   \033[33m                      \033[41m              \033[0m     \033[043m        \033[0m"
	@echo "   \033[33m                    \033[41m                        \033[043m     \033[0m"
	@echo "   \033[33m                    \033[100m        \033[43m     \033[0m\033[100m   \033[0m\033[43m   \033[0m  \033[100m        \033[0m"
	@echo "   \033[33m                  \033[100m  \033[43m   \033[0m\033[100m   \033[0m\033[43m       \033[0m\033[100m   \033[0m\033[43m     \033[0m\033[100m        \033[0m"
	@echo "   \033[33m                  \033[100m  \033[43m░░░\033[0m\033[100m      \033[0m\033[43m       \033[0m\033[100m   \033[0m\033[43m        \033[0m\033[100m  \033[0m"
	@echo "   \033[33m                  \033[100m     \033[43m░░░░░░░░░░\033[0m\033[100m              \033[0m"
	@echo "   \033[33m                       \033[43m░░░░░░░░░░░░░░░░░░\033[0m\033[100m   \033[0m"
	@echo "   \033[33m             \033[100m             \033[41m   \033[0m\033[100m       \033[0m\033[41m   \033[0m\033[100m  \033[0m"
	@echo "   \033[33m           \033[100m                  \033[41m   \033[0m\033[100m       \033[0m\033[41m  \033[0m     \033[100m  \033[0m"
	@echo "   \033[33m         \033[043m    \033[0m\033[100m                \033[41m            \033[0m     \033[100m  \033[0m"
	@echo "   \033[33m         \033[043m      \033[0m   \033[041m     \033[0m\033[100m   \033[41m      \033[0m\033[043m  \033[0m\033[041m     \033[0m\033[043m  \033[0m\033[041m   \033[0m\033[100m    \033[0m"
	@echo "   \033[33m           \033[043m░░\033[0m  \033[100m   \033[0m\033[041m                          \033[0m\033[100m    \033[0m"
	@echo "   \033[33m             \033[100m       \033[0m\033[041m                        \033[0m\033[100m    \033[0m"
	@echo "   \033[33m           \033[100m       \033[0m\033[041m                  \033[0m"
	@echo "   \033[33m           \033[100m  \033[0m     \033[041m          \033[0m"
	@echo " "
	@echo " "
	@echo "\033[043m                                                              \033[0m"
	@echo "\033[043m                         \033[030mC O R E W A R                        \033[0m"
	@echo "\033[043m                           \033[035mTeam DAMN                          \033[0m"
	@echo "\033[043m           \033[030mdlouise    atrupin    mfroehly    nle-bret         \033[0m"
	@echo "\033[043m                                                              \033[0m"
	@echo " "

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
