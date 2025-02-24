# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 17:14:53 by mpoplow           #+#    #+#              #
#    Updated: 2025/02/24 14:41:07 by mpoplow          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

CFLAGS	:= -Wall -Wextra -Werror -MMD
# -fsanitize=address -g

# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#
# 	FILES																		#
# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#

CFILES	:= $(addprefix src/, \
		test.c )

OFILES	= $(addprefix src/O_D_FILES/, $(notdir $(CFILES:.c=.o)))
DFILES	= $(addprefix src/O_D_FILES/, $(notdir $(CFILES:.c=.d)))

# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#
# 	RULES																		#
# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#

all: $(NAME)

$(NAME): $(OFILES) $(DFILES)
	@make all -sC libft
	@$(CC) $(OFILES) libft/libft.a -o $(NAME)
	@echo "\033[1;32mCREATE PROGRAM: $(NAME)\033[0m"

src/O_D_FILES/%.o: src/%.c | src/O_D_FILES
	@$(CC) $(CFLAGS) -MMD -MP -g -c $< -o $@

src/O_D_FILES:
	@mkdir -p $@

clean:
	@echo "\033[1;33mCLEAN $(NAME)\033[0m"
	@make fclean -C libft
	@rm -f $(OFILES) $(DFILES)
	@rm -rf src/O_D_Files

fclean: clean
	@echo "\033[1;33mREMOVE PROGRAM: $(NAME)\033[0m"
	@rm -f $(NAME)

re: clean all

prep: fclean all
	make clean

.SILENT:  $(OFILES) $(DFILES)
.PHONY: all clean fclean re prep