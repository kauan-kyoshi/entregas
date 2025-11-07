NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I/usr/local/include

SRCS_DIR = src
SRCS = 	main.c \
		parse_main.c \
		parse_tokens.c \
		parse_checks.c \
		parse_index.c \
		stack_utils.c \
		sort_small.c \
		sort_many.c \
		sort_router.c \
		ops_swap.c \
		ops_push.c \
		ops_push_utils.c \
		ops_rotate.c \
		ops_rev_rotate.c \
		utils_num.c \
		utils_checks.c \
		utils_mem.c \
		utils_nodes.c \
		utils_search.c \
		checker_ops.c

SRCS_FULL = $(addprefix $(SRCS_DIR)/, $(SRCS))


OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CHECKER = checker
CHECKER_SRC = $(SRCS_DIR)/checker.c
CHECKER_OBJ = $(OBJ_DIR)/checker.o

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "Code by: Kyoshi Lima ^-^ "

$(CHECKER): $(CHECKER_OBJ) $(filter-out $(OBJ_DIR)/main.o,$(OBJS)) $(LIBFT)
	@$(CC) $(CFLAGS) $(filter-out $(OBJ_DIR)/main.o,$(OBJS)) $(CHECKER_OBJ) $(LIBFT) -o $(CHECKER)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME) $(CHECKER)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re


