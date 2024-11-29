NAME = pipex
LIBFT = libft.a

LIBFT_PATH = ./libft/

SRC =	absolute_path.c \
		lst_utils.c \
		utils.c \
		pipeline.c \
		main.c

CC = cc
FLAGS = -Wall -Wextra -Werror
# -g -fsanitize=address 
RM = rm -f
OBJ = $(SRC:.c=.o)
INCLUDE = pipex.h 


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(LIBFT_PATH) -lft
	@echo "Compilation done"

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@echo "LIBFT created"

%.o: %.c
	@$(CC) $(FLAGS) -c -o $@ $<

clean: 
	@$(MAKE) -C $(LIBFT_PATH) clean > /dev/null 2>&1
	@$(RM) $(OBJ) > /dev/null 2>&1
	@echo "Clean done"

fclean: clean
	@$(MAKE) -C $(LIBFT_PATH) fclean > /dev/null 2>&1
	@$(RM) $(NAME) > /dev/null 2>&1
	@echo "Fclean done"

re: fclean all

.PHONY: clean all re fclean
