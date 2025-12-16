# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alacroix <alacroix@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 12:50:54 by alacroix          #+#    #+#              #
#    Updated: 2024/11/19 11:56:59 by alacroix         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS += -Wall -Werror -Wextra
NAME = libft.a

SOURCES_BONUS = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstmap_bonus.c

SOURCES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
		ft_substr.c ft_tolower.c ft_toupper.c

OBJ = $(SOURCES:.c=.o)
OBJ_BONUS = $(SOURCES_BONUS:.c=.o)

GREEN = \033[32m
RESET = \033[0m

all: $(NAME)
	@echo "\033[32m  _      _  _       __  _                                       \033[0m"
	@echo "\033[33m | |    (_)| |     / _|| |                                      \033[0m"
	@echo "\033[34m | |     _ | |__  | |_ | |_                                    \033[0m"
	@echo "\033[36m | |    | || '_ \ |  _|| __|                                   \033[0m"
	@echo "\033[35m | |____| || |_) || |  | |_                                    \033[0m"
	@echo "\033[31m \\_____/|_||_.__/ |_|   \\__|                                   \033[0m"
	@echo "\033[33m                                                               \033[0m"
	@echo "\033[32m                                 _        _              _   _ \033[0m"
	@echo "\033[33m                                | |      | |            | | | | \033[0m"
	@echo "\033[34m   ___   ___   _ __ ___   _ __  | |  ___ | |_   ___   __| | | | \033[0m"
	@echo "\033[36m  / __| / _ \ | ._ . _ \ | '_ \ | | / _ \| __| / _ \ / _. | | | \033[0m"
	@echo "\033[35m | (__ | (_) || | | | | || |_) || ||  __/| |_ |  __/| (_| | |_| \033[0m"
	@echo "\033[31m  \___| \___/ |_| |_| |_|| .__/ |_| \___| \__| \___| \__._| (_) \033[0m"
	@echo "\033[33m                         | |                                   \033[0m"
	@echo "\033[32m                         |_|                                   \033[0m"


$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	@echo "$(RED) Suppression des fichiers objets...$(RESET)"
	rm -f $(OBJ) $(OBJ_BONUS)

fclean:
	@echo "$(RED) Suppression complète de $(NAME) et des objets...$(RESET)"
	rm -f $(NAME) $(OBJ) $(OBJ_BONUS)

bonus: $(OBJ_BONUS)
	@echo "\033[38;5;129m ______                            \033[0m"
	@echo "\033[38;5;57m| ___ \                           \033[0m"
	@echo "\033[38;5;54m| |_/ /  ___   _ __   _   _  ___ \033[0m"
	@echo "\033[38;5;186m| ___ \ / _ \ | '_ \ | | | |/ __| \033[0m"
	@echo "\033[38;5;13m| |_/ /| (_) || | | || |_| |\__ \ \033[0m"
	@echo "\033[38;5;55m\____/  \___/ |_| |_| \__,_||___/  \033[0m"
	@echo "                                 "
	@echo "                                 "
	@echo "\033[38;5;129m                     _     _     \033[0m"
	@echo "\033[38;5;57m                    | |   | |    \033[0m"
	@echo "\033[38;5;54m _ __    __ _  _ __ | |_  | |    \033[0m"
	@echo "\033[38;5;186m| '_ \  / _. || '__|| __| | |    \033[0m"
	@echo "\033[38;5;13m| |_) || (_| || |   | |_  |_|    \033[0m"
	@echo "\033[38;5;55m| .__/  \__,_||_|    \__| (_)    \033[0m"
	@echo "\033[38;5;57m| |                               \033[0m"
	@echo "\033[38;5;186m|_|                              \033[0m"
	@echo "$(GREEN)    .     .       .  .   . .   .   . .    +  .  $(RESET)"
	@echo "$(GREEN)  .     .  :     .    .. :. .___---------___. $(RESET)"
	@echo "$(GREEN)       .  .   .    .  :.:. _\".^ .^ ^.  '.. :\"-_. . $(RESET)"
	@echo "$(GREEN)    .  :       .  .  .:../:            . .^  :.:\. $(RESET)"
	@echo "$(GREEN)        .   . :: +. :.:/: .   .    .        . . .:\ $(RESET)"
	@echo "$(GREEN) .  :    .     . _ :::/:               .  ^ .  . .:/ $(RESET)"
	@echo "$(GREEN)  .. . .   . - : :.:./.                        .  .:/ $(RESET)"
	@echo "$(GREEN)  .      .     . :..|:                    .  .  ^. .:| $(RESET)"
	@echo "$(GREEN)    .       . : : ..||        .                . . !:| $(RESET)"
	@echo "$(GREEN)  .     . . . ::. ::\(                           . :)\/ $(RESET)"
	@echo "$(GREEN) .   .     : . : .:.|. ######              .#######::| $(RESET)"
	@echo "$(GREEN)  :.. .  :-  : .:  ::|.#######           ..########:| $(RESET)"
	@echo "$(GREEN) .  .  .  ..  .  .. :\ ########          :######## :/ $(RESET)"
	@echo "$(GREEN)  .        .+ :: : -.:\ ########       . ########.:/ $(RESET)"
	@echo "$(GREEN)    .  .+   . . . . :.:\. #######       #######..:/ $(RESET)"
	@echo "$(GREEN)      :: . . . . ::.:..:.\           .   .   ..:/ $(RESET)"
	@echo "$(GREEN)   .   .   .  .. :  -::::.\.       | |     . .:/ $(RESET)"
	@echo "$(GREEN)      .  :  .  .  .-:.\":.::.\             ..:/ $(RESET)"
	@echo "$(GREEN) .      -.   . . . .: .:::.:.\.           .:/ $(RESET)"
	@echo "$(GREEN) .   .   .  :      : ....::_:..:\   ___.  :/ $(RESET)"
	@echo "$(GREEN)    .   .  .   .:. .. .  .: :.:.:\       :/ $(RESET)"
	@echo "$(GREEN)      +   .   .   : . ::. :.:. .:.|\  .:/| $(RESET)"
	@echo "$(GREEN)     .         +   .  .  ...:: ..|  --.:| $(RESET)"
	@echo "$(GREEN) .      . . .   .  .  . ... :..:..\"(  ..)\"$(RESET)"
	ar rcs $(NAME) $(OBJ_BONUS)

re: fclean all

.PHONY: all clean fclean bonus re
