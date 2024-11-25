NAME = fdf
TARGET = FdF
TARGET_FILES = $(shell find $(TARGET) -name '*.c') $(shell find $(TARGET) -name '*.h')
BIN_DIR = build

$(BIN_DIR)/$(NAME): $(TARGET)/$(NAME) | $(BIN_DIR)
	@cp $(TARGET)/$(NAME) $(BIN_DIR)/$(NAME)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET)/$(NAME): $(TARGET_FILES)
	@make -C $(TARGET)

clean:
	@make clean -C $(TARGET)

fclean:
	@make fclean -C $(TARGET)
	rm -rf $(BIN_DIR)/$(NAME) $(BIN_DIR)
