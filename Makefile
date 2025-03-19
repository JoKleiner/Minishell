# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joklein <joklein@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/09 16:13:10 by mpoplow           #+#    #+#              #
#    Updated: 2025/03/19 15:14:26 by joklein          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -g
# -fsanitize=address -g


# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#
# 	Directories																	#
# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#

LIBFT_DIR   	:= libft
SRC_DIR         := src
INPUT_DIR		:= $(SRC_DIR)/input
COMMANDS_DIR	:= $(SRC_DIR)/commands
UTILS_DIR		:= $(SRC_DIR)/utils
OBJ_D_DIR		:= obj_d


# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#
# 	FILES																		#
# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#

CFILES_SRCS		:= $(addprefix $(SRC_DIR)/, minishell_main.c signal.c process.c stream.c syntax.c)
CFILES_INPUT	:= $(addprefix $(INPUT_DIR)/, input_handle.c redirect_out.c redirect_in.c heredoc.c dollar_change.c create_args.c dollar_quote.c)
CFILES_CMD		:= $(addprefix $(COMMANDS_DIR)/, exe_commands.c error_cmd.c cd.c echo.c env.c exit.c export.c pwd.c unset.c)
CFILES_UTILS	:= $(addprefix $(UTILS_DIR)/, dollar_utils.c envp_check_utils.c envp_change_utils.c free_utils.c str_array_utils.c mini_utils.c)

SRCS    = $(CFILES_SRCS) $(CFILES_INPUT) $(CFILES_CMD) $(CFILES_UTILS)
OFILES	= $(addprefix $(OBJ_D_DIR)/, $(SRCS:.c=.o))
DFILES	= $(addprefix $(OBJ_D_DIR)/, $(SRCS:.c=.d))

# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#
# 	RULES																		#
# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#

all: $(NAME)


$(NAME): $(OFILES) $(DFILES)
	@make -sC $(LIBFT_DIR)
	@$(CC) $(OFILES) $(LIBFT_DIR)/libft.a -o $(NAME) -lreadline -lhistory -ltermcap
	@echo "\033[1;32mCREATE PROGRAM: $(NAME)\033[0m"


$(OBJ_D_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP -g -c $< -o $@


clean:
	@make clean -C $(LIBFT_DIR)
	@if [ -d $(OBJ_D_DIR) ]; then \
		echo "\033[1;33mCLEAN $(NAME)\033[0m"; \
		rm -f $(OFILES) $(DFILES); \
		rm -rf $(OBJ_D_DIR); \
	fi

fclean: clean
	@make fclean -C libft
	@if [ -f "$(NAME)" ]; then \
		echo "\033[1;33mREMOVE PROGRAM: $(NAME)\033[0m"; \
		rm -f $(NAME); \
	fi

re: fclean all

prep: re
	make clean
	clear

.SILENT:  $(OFILES) $(DFILES)
.PHONY: all clean fclean re prep
