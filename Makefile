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

SRC_MALLOC = ft_malloc/arena.c ft_malloc/ft_malloc.c ft_malloc/memblock.c
SRC_FREE = ft_free.c
SRC_GLOBALS = globals.c
SRC_REALLOC = ft_realloc.c
SRC_SHOW_ALLOC = ft_show_alloc_mem.c ft_show_alloc_mem_ex.c

SRC = $(SRC_MALLOC) $(SRC_FREE) $(SRC_GLOBALS) $(SRC_REALLOC) $(SRC_SHOW_ALLOC)

SRCS = $(addprefix $(SRC_DIR)/,$(SRC))
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(OBJ_DIR) $(LIBFT) $(NAME) $(SYMLINK_NAME)

$(SYMLINK_NAME) : $(NAME)
	ln -s $(NAME) $(SYMLINK_NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) -shared -o $(NAME) $(OBJ) $(LIBFT)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_INCLUDE) -lpthread -c -fPIC $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

test: $(SYMLINK_NAME)
	$(CC) $(CFLAGS) $(TEST_SRC) -I$(INC_DIR) -L. -lft_malloc -Wl,-rpath,'$$ORIGIN' -o $(TEST_NAME)

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
