include Includes.mk
CC = cc 

LIBFT= libft
LINKERS= -L./$(LIBFT)/ -Lncurses -lft -lncurses
CFLAGS = -Wall -Werror -Werror -std=c99 -Ofast -I./includes/ -I./$(LIBFT)/includes/ 

OBJ_DIR = build
NAME = Game2048 

SRCSDIR = $(addprefix src/,$(SRCS))
INCLUDES_DIR = $(addprefix includes/,$(INCLUDES))

SRCS_OBJ = $(SRCSDIR:%.c=$(OBJ_DIR)/%.o)

all: libft $(NAME)

libft:
	@make -C $(LIBFT)
$(NAME):$(SRCS_OBJ)
	@make -C $(LIBFT)
	$(CC) $(SRCS_OBJ) $(CFLAGS) $(LINKERS) -o $(NAME)
$(OBJ_DIR)/%.o: %.c  $(INCLUDES_DIR)
	@mkdir -p $(dir $@)
	$(CC) $< $(CFLAGS) -c -o $@
clean:
	@make -C libft fclean
	@rm -rf $(OBJ_DIR)
fclean:clean
	@rm -f $(NAME) 
re: fclean all

.PHONY: all clean fclean re libft 