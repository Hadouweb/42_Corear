CC = gcc -Werror -Wextra -Wall

SRCPATH = ./srcs
UTILPATH = $(SRCPATH)/util
SETDATA = $(SRCPATH)/set_data
PRINT = $(SRCPATH)/print
PARSING = $(SRCPATH)/parsing
ERROR = $(SRCPATH)/error

INCPATH = ./includes

LIBFT = ./libft

HEADER = -I $(LIBFT)/includes -I $(INCPATH)

LIB = $(LIBFT)/libft.a 

SRC = $(SRCPATH)/main.c\
	  $(UTILPATH)/asm_util.c\
	  $(UTILPATH)/asm_debug.c\
	  $(UTILPATH)/asm_cursor.c\
	  $(SETDATA)/asm_set_btcode.c\
	  $(SETDATA)/asm_read_file.c\
	  $(SETDATA)/asm_push_data.c\
	  $(SETDATA)/asm_init.c\
	  $(PRINT)/asm_write.c\
	  $(PRINT)/asm_print_success.c\
	  $(PRINT)/asm_print_error.c\
	  $(PARSING)/asm_parsing.c\
	  $(PARSING)/asm_parsing_header.c\
	  $(ERROR)/asm_util_error.c\
	  $(ERROR)/asm_error_param.c\
	  $(ERROR)/asm_error_param_syntax.c\
	  $(ERROR)/asm_error_label.c\
	  $(ERROR)/asm_error_instr.c\
	  $(ERROR)/asm_error.c\

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
