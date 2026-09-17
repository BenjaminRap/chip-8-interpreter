NAME		:= chip-8-interpreter

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -MMD -MP -Iheaders
LDFLAGS		:= -I/usr/include/SDL2 -D_REENTRANT
LDLIBS		:= -lSDL2

SRC_DIR		:= src
OBJ_DIR		:= build


SRC_FILES	:=	main.c \
				sdl_handler.c \
				interpreter.c \
				instructions.c \
				execute_instruction.c \
				handle_events.c \
				read_arguments.c
SRC			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			:= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP			:= $(OBJ:.o=.d)

# ─────────────────────────────────────────────
# Default target
# ─────────────────────────────────────────────

.PHONY: all
all: $(NAME)

# ─────────────────────────────────────────────
# Linking
# ─────────────────────────────────────────────

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# ─────────────────────────────────────────────
# Compilation
# ─────────────────────────────────────────────

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ─────────────────────────────────────────────
# Dependencies
# ─────────────────────────────────────────────

-include $(DEP)

# ─────────────────────────────────────────────
# Cleaning
# ─────────────────────────────────────────────

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all

# ─────────────────────────────────────────────
# Debug / Release
# ─────────────────────────────────────────────

.PHONY: debug
debug: CFLAGS += -g3 -O0
debug: re

.PHONY: release
release: CFLAGS += -O2
release: re
