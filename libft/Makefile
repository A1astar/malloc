# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/04 15:27:43 by alacroix          #+#    #+#              #
#    Updated: 2026/01/20 11:17:59 by alacroix         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra

INCDIR = includes
OBJDIR = obj

CONV_SRC = conv/ft_atoi.c  conv/ft_atol.c conv/ft_atoll.c conv/ft_itoa.c
FD_SRC = fd/ft_putchar_fd.c fd/ft_putendl_fd.c fd/ft_putnbr_fd.c fd/ft_putstr_fd.c fd/get_next_line.c
FREE_SRC = free/ft_free_tab.c
IS_SRC = is/ft_isalnum.c is/ft_isalpha.c is/ft_isascii.c is/ft_isdigit.c is/ft_isprint.c
LST_SRC = lst/ft_lstadd_back.c lst/ft_lstadd_front.c lst/ft_lstclear.c lst/ft_lstdelone.c lst/ft_lstiter.c lst/ft_lstlast.c lst/ft_lstmap.c lst/ft_lstnew.c lst/ft_lstsize.c
MATH_SRC = math/ft_pow.c math/ft_sqrt.c
MEM_SRC = mem/ft_bzero.c mem/ft_calloc.c mem/ft_memchr.c mem/ft_memcmp.c mem/ft_memcpy.c mem/ft_memmove.c mem/ft_memset.c
STR_SRC = str/ft_split.c str/ft_strchr.c str/ft_strdup.c str/ft_striteri.c str/ft_strjoin.c str/ft_strlcat.c str/ft_strlcpy.c str/ft_strlen.c str/ft_strmapi.c str/ft_strncmp.c str/ft_strnstr.c str/ft_strrchr.c str/ft_strtrim.c str/ft_substr.c str/ft_tolower.c str/ft_toupper.c str/ft_strsize_comp.c str/ft_tabsize.c str/ft_strndup.c
FT_PRINTF_SRC = ft_printf/ft_printf.c ft_printf/ft_printf_utils.c ft_printf/ft_printf_utils2.c

SRC = $(CONV_SRC) $(DYNARRAY_SRC) $(FD_SRC) $(FREE_SRC) $(IS_SRC) $(LST_SRC) $(MATH_SRC) $(MEM_SRC) $(STR_SRC) $(FT_PRINTF_SRC)
OBJ = $(patsubst %.c, $(OBJDIR)/%.o, $(SRC))


all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
