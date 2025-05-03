NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

SRC_FILES = philo.c utils.c args.c time_utils.c init.c \
			philo_routine.c cleanup.c simulation.c actions.c \
			status_utils.c monitoring.c

SRCS_DIR = src
SRCS = $(addprefix $(SRCS_DIR)/, $(SRC_FILES))

OBJ_DIR = obj
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

INC_DIR = include
INC = -I$(INC_DIR)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
BLUE = \033[0;34m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) oluşturuldu$(RESET)"

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "$(BLUE)  → Derlendi: $< $(RESET)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)  → Klasör oluşturuldu: $(OBJ_DIR)$(RESET)"

clean:
	$(RM) -r $(OBJ_DIR)
	@echo "$(RED)✗ Nesne dosyaları ($(OBJ_DIR)) temizlendi$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED)✗ Program ($(NAME)) temizlendi$(RESET)"

re: fclean all

.PHONY: all clean fclean re
