NAME = fdf
TARGET = FdF
TARGET_FILES = $(shell find $(TARGET) -name '*.c') $(shell find $(TARGET) -name '*.h')
BIN_DIR = build

all: $(BIN_DIR)/$(NAME)

$(TARGET)/$(NAME): $(TARGET_FILES)
	@make -C $(TARGET)

$(BIN_DIR)/$(NAME): $(TARGET)/$(NAME) | $(BIN_DIR)
	@cp $(TARGET)/$(NAME) $(BIN_DIR)/$(NAME)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	@make clean -C $(TARGET)

fclean:
	rm -rf $(BIN_DIR)/$(NAME) $(BIN_DIR)
	@make fclean -C $(TARGET)

re: fclean all

.PHONY: all clean fclean re
