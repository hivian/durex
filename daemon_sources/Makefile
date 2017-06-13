NAME 		= Durex
CC 	 		= gcc -pthread -lcrypt -Wall -Wextra -Werror

SRC_DIR		= srcs
INC_DIR		= incs

SRCS  		= main.c \
			  error.c \
			  trojan.c \
			  connection.c \
			  thread.c \
			  utility.c \
			  shell.c \

OBJ  		= $(SRCS:%.c=objs/%.o)

WHITE		=	\033[0m
GREEN		=	\033[32m
BLUE		=	\033[1;34m
CYAN		=	\033[36m
RED			=	\033[31m
GREY		=	\033[1;30m
YELLOW		=	\033[33m

all: objs $(NAME)

objs :
	@mkdir objs

$(NAME): $(OBJ)
	@printf "Compiling Durex ... "
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "Done"

objs/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

clean:
	@rm -rf objs

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
