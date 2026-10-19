# ============================================================================ #
#                                   CONFIG                                     #
# ============================================================================ #

NAME      := moulinette

CC        := cc
CFLAGS    := -Wall -Wextra -Werror -g3
CPPFLAGS  := -I include -MMD -MP

SRC_DIR   := src
OBJ_DIR   := .obj

SRC       := main.c
SRC       := $(addprefix $(SRC_DIR)/, $(SRC))
OBJ       := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP       := $(OBJ:.o=.d)

ARGS      ?=

# AddressSanitizer : make re SAN=1
ifeq ($(SAN), 1)
    CFLAGS += -fsanitize=address
endif

VALGRIND  := valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

# ============================================================================ #
#                                  COULEURS                                    #
# ============================================================================ #

GREEN     := \033[1;32m
BLUE      := \033[1;34m
YELLOW    := \033[1;33m
RED       := \033[1;31m
RESET     := \033[0m

# ============================================================================ #
#                                   RÈGLES                                     #
# ============================================================================ #

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@
	@printf "$(GREEN)✔ $@ compilé$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@printf "$(BLUE)→ %s$(RESET)\n" "$<"

-include $(DEP)

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(YELLOW)✗ objets supprimés$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)✗ $(NAME) supprimé$(RESET)\n"

re: fclean
	@$(MAKE) --no-print-directory all

# ============================================================================ #
#                                    OUTILS                                    #
# ============================================================================ #

run: all
	./$(NAME) $(ARGS)

valgrind: all
	$(VALGRIND) ./$(NAME) $(ARGS)

.PHONY: all clean fclean re run valgrind