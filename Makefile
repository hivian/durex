NAME 		= Durex
CC 	 		= gcc -std=c11
#-Wall -Wextra -Werror

SRC_DIR		= srcs
INC_DIR		= incs

SRCS  		= main.c \
			  error.c \

OBJ  		= $(SRCS:%.c=objs/%.o)

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
