TARGET = FdF
FDF_NAME = fdf
BIN_DIR = build

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lXext -lX11 -lm -lz -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx_Linux

LIB_DIR = $(TARGET)/lib
MLX_DIR = $(LIB_DIR)/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
LIBFT_DIR = $(LIB_DIR)/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

HEADER_DIR = $(TARGET)/inc
HEADER = $(HEADER_DIR)/fdf.h
INCLUDES = -I$(HEADER_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)

SRCS_DIR = $(TARGET)/src
SRCS_FILES = parsing.c drawing.c main.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS_DIR = $(TARGET)/objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

TEST_DIR = tests
TEST_HEADER = $(TEST_DIR)/tests.h
TEST_INCLUDES = $(INCLUDES) -I$(TEST_DIR)
TEST_OBJS_DIR = tests/objs
TEST_FILES = test_parsing.c test_drawing.c

TEST_PARSING_DIR = $(TEST_DIR)/parsing_functions
TEST_PARSING_FILES = test_parse_cell.c test_add_point.c
TEST_PARSING_OBJS = $(addprefix $(TEST_OBJS_DIR)/, $(TEST_PARSING_FILES:.c=.o))

TEST_DRAWING_DIR = $(TEST_DIR)/drawing_functions
TEST_DRAWING_FILES = test_img_pix_put.c
TEST_DRAWING_OBJS = $(addprefix $(TEST_OBJS_DIR)/, $(TEST_DRAWING_FILES:.c=.o))

TEST_OBJS = $(addprefix $(TEST_OBJS_DIR)/, $(TEST_FILES:.c=.o)) \
			$(TEST_PARSING_OBJS) \
			$(TEST_DRAWING_OBJS)

all: $(BIN_DIR)/$(FDF_NAME) \
	 $(BIN_DIR)/tests/test_parsing.out \
	 $(BIN_DIR)/tests/test_drawing.out

clean:
	rm -rf $(OBJS) $(OBJS_DIR) $(TEST_OBJS) $(TEST_OBJS_DIR)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(BIN_DIR) $(MLX_LIB) $(LIBFT_LIB)

re: fclean all

$(BIN_DIR)/$(FDF_NAME): $(LIBFT_LIB) $(MLX_LIB) $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(BIN_DIR)/$(FDF_NAME)

$(LIBFT_LIB):
	@make debug -C $(LIBFT_DIR)

$(MLX_LIB):
	@make -C $(MLX_DIR)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BIN_DIR)/tests:
	mkdir -p $(BIN_DIR)/tests

$(TEST_OBJS_DIR):
	mkdir -p $(TEST_OBJS_DIR)

$(TEST_OBJS_DIR)/%.o: $(TEST_DIR)/%.c $(HEADER) $(TEST_HEADER) | $(TEST_OBJS_DIR)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -c $< -o $@

$(BIN_DIR)/tests/test_parsing.out: \
	$(OBJS_DIR)/parsing.o \
	$(TEST_OBJS_DIR)/test_parsing.o \
	$(TEST_PARSING_OBJS) \
	$(LIBFT_LIB) $(MLX_LIB) | $(BIN_DIR)/tests
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(TEST_OBJS_DIR)/%.o: $(TEST_PARSING_DIR)/%.c $(HEADER) $(TEST_HEADER) | $(TEST_OBJS_DIR)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -c $< -o $@

$(BIN_DIR)/tests/test_drawing.out: \
	$(OBJS_DIR)/drawing.o \
	$(TEST_OBJS_DIR)/test_drawing.o \
	$(TEST_DRAWING_OBJS) \
	$(LIBFT_LIB) $(MLX_LIB) | $(BIN_DIR)/tests
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(TEST_OBJS_DIR)/%.o: $(TEST_DRAWING_DIR)/%.c $(HEADER) $(TEST_HEADER) | $(TEST_OBJS_DIR)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -c $< -o $@

.PHONY: all clean fclean re
