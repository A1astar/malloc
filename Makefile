CC = cc
CFLAGS += -Wall -Wextra -Werror -std=gnu99

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
SYMLINK_NAME = libft_malloc.so
TEST_NAME = malloc_test

export LD_LIBRARY_PATH=./

SRC_DIR = ./src
INC_DIR = ./includes
OBJ_DIR = ./obj

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE := $(LIBFT_DIR)/includes
LDFLAGS = -L$(LIBFT_DIR)
LIBS = $(LIBFT)

AR = ar
ARFLAGS = rcs

TEST_SRC = test/main.c
SRC = free.c malloc.c realloc.c show_alloc_mem.c globals.c

SRCS = $(addprefix $(SRC_DIR)/,$(SRC))
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(OBJ_DIR) $(LIBFT) $(NAME) $(SYMLINK_NAME)

$(SYMLINK_NAME) : $(NAME)
	ln -s $(NAME) $(SYMLINK_NAME)

$(NAME) : $(OBJ)
	$(CC) -shared -o $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT) -pthread -c -fPIC $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

test: $(SYMLINK_NAME)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(SYMLINK_NAME)
	rm -f $(TEST_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test
.DEFAULT_GOAL := all
