# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/20 14:01:05 by jaguillo          #+#    #+#              #
#    Updated: 2015/02/10 20:52:51 by jaguillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE = $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so

TEST = test

H_DIR = .
C_DIR = srcs
O_DIR = o

FLAGS = -Wall -Wextra -Werror -O2 -fPIC
DEBUG = 0

C_FILES = $(shell find $(C_DIR) -type f -print | grep "\.c")
C_DIRS = $(shell find $(C_DIR) -type d -print)

O_DIRS = $(C_DIRS:$(C_DIR)/%=$(O_DIR)/%)
O_FILES = $(C_FILES:$(C_DIR)/%.c=$(O_DIR)/%.o)

all:
	@if [ "$(DEBUG)" -eq "1" ]; then \
		make -j4 _debug $(NAME); else \
		make -j4 $(NAME); fi

$(NAME): $(O_FILES)
	@gcc $(FLAGS) -shared -o $@ $^ && printf "\033[0;32m" || printf "\033[0;31m"
	@printf "%-34s \033[1;30m<<--\033[0;0m\n" "$@"
	@ln -s $@ $(LINK)

$(O_DIR)/%.o: $(C_DIR)/%.c
	@mkdir -p $(O_DIRS) $(O_DIR) 2> /dev/null || echo "" > /dev/null
	@gcc $(FLAGS) -I$(H_DIR) -o $@ -c $< \
	&& printf "\033[0;0m%-34s\033[1;30m -->>\t\033[0;32m$@\033[0;0m\n" "$<" \
	|| (printf "\033[0;0m%-34s\033[1;30m -->>\t\033[0;31m$@\033[0;0m\n" "$<" \
		&& exit 1)

debug: _debug all

clean:
	@rm $(O_FILES) 2> /dev/null || echo "" > /dev/null
	@rmdir $(O_DIRS) $(O_DIR) 2> /dev/null || echo "" > /dev/null

fclean: clean
	@rm $(NAME) $(TEST) $(LINK) 2> /dev/null || echo "" > /dev/null

re: fclean all

rebug: fclean debug

$(TEST): all
	@gcc test.c $(O_FILES) -g -o $@ && printf "\033[0;32m" || printf "\033[0;31m"
	@printf "%-34s \033[1;30m<<--\033[0;0m\n" "$@"

_debug:
	$(eval FLAGS = -Wall -Wextra -fPIC -g -D DEBUG_MODE)
	$(eval DEBUG = 1)

.PHONY: all debug clean fclean re rebug _debug
