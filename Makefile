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
SRCS_FILES = vectorize.c parse.c render.c main.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJS_DIR = $(TARGET)/objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS_FILES:.c=.o))

TEST_DIR = tests
TEST_HEADER = $(TEST_DIR)/tests.h
TEST_INCLUDES = $(INCLUDES) -I$(TEST_DIR)
TEST_OBJS_DIR = tests/objs
TEST_FILES =	test_parse.c \
				test_render.c

TEST_PARSE_DIR = $(TEST_DIR)/parse_functions
TEST_PARSE_FILES =	test_parse_cell.c \
						test_add_point.c  \
						test_parse_line.c \
						test_parse_mapfile.c \
						test_extract_points.c
TEST_PARSE_OBJS = $(addprefix $(TEST_OBJS_DIR)/, $(TEST_PARSE_FILES:.c=.o))

TEST_VECTORIZE_DIR = $(TEST_DIR)/vectorize_functions
TEST_VECTORIZE_FILES =	test_set_vector_properties.c \
						test_add_vector.c \
						test_generate_vector_list.c
TEST_VECTORIZE_OBJS = $(addprefix $(TEST_OBJS_DIR)/, $(TEST_VECTORIZE_FILES:.c=.o))

TEST_RENDER_DIR = $(TEST_DIR)/render_functions
TEST_RENDER_FILES = test_img_pix_put.c
TEST_RENDER_OBJS = $(addprefix $(TEST_OBJS_DIR)/, $(TEST_RENDER_FILES:.c=.o))

TEST_OBJS = $(addprefix $(TEST_OBJS_DIR)/, $(TEST_FILES:.c=.o)) \
			$(TEST_PARSE_OBJS) \
			$(TEST_RENDER_OBJS)

all: $(BIN_DIR)/$(FDF_NAME) \
	 $(BIN_DIR)/tests/test_parse.out \
	 $(BIN_DIR)/tests/test_render.out \
	 $(BIN_DIR)/tests/test_vectorize.out

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

$(BIN_DIR)/tests/test_parse.out: \
	$(OBJS_DIR)/parse.o \
	$(TEST_OBJS_DIR)/test_parse.o \
	$(TEST_PARSE_OBJS) \
	$(LIBFT_LIB) $(MLX_LIB) | $(BIN_DIR)/tests
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(TEST_OBJS_DIR)/%.o: $(TEST_PARSE_DIR)/%.c $(HEADER) $(TEST_HEADER) | $(TEST_OBJS_DIR)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -c $< -o $@

$(BIN_DIR)/tests/test_render.out: \
	$(OBJS_DIR)/render.o \
	$(TEST_OBJS_DIR)/test_render.o \
	$(TEST_RENDER_OBJS) \
	$(LIBFT_LIB) $(MLX_LIB) | $(BIN_DIR)/tests
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(TEST_OBJS_DIR)/%.o: $(TEST_RENDER_DIR)/%.c $(HEADER) $(TEST_HEADER) | $(TEST_OBJS_DIR)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -c $< -o $@

$(BIN_DIR)/tests/test_vectorize.out: \
	$(OBJS_DIR)/vectorize.o \
	$(TEST_OBJS_DIR)/test_vectorize.o \
	$(TEST_VECTORIZE_OBJS) \
	$(LIBFT_LIB) $(MLX_LIB) | $(BIN_DIR)/tests
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(TEST_OBJS_DIR)/%.o: $(TEST_VECTORIZE_DIR)/%.c $(HEADER) $(TEST_HEADER) | $(TEST_OBJS_DIR)
	$(CC) $(CFLAGS) $(TEST_INCLUDES) -c $< -o $@

.PHONY: all clean fclean re
