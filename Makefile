# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpoplow <mpoplow@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/09 16:13:10 by mpoplow           #+#    #+#              #
#    Updated: 2025/03/25 15:18:47 by mpoplow          ###   ########.fr        #
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
BLTIN_DIR		:= $(SRC_DIR)/builtin_cmds
UTILS_DIR		:= $(SRC_DIR)/utils
OBJ_D_DIR		:= obj_d


# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#
# 	FILES																		#
# *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*	#

CFILES_BLTIN	:= $(addprefix $(BLTIN_DIR)/, cd.c echo.c env.c exit.c export.c export_empty.c pwd.c unset.c)
CFILES_SRCS		:= $(addprefix $(SRC_DIR)/, minishell_main.c signal.c process.c stream.c syntax.c init_copy_env.c pipe.c pipe_expan.c)
CFILES_INPUT	:= $(addprefix $(INPUT_DIR)/, input_handle.c redirect_out.c redirect_in.c heredoc.c dollar_change.c create_args.c dollar_quote.c dollar_handle.c heredoc_child.c)
CFILES_CMD		:= $(addprefix $(COMMANDS_DIR)/, builtin.c cmd_in_path.c slash_dot_syntax.c isdir.c exe_commands.c error_cmd.c executable.c)
CFILES_UTILS	:= $(addprefix $(UTILS_DIR)/, dollar_utils.c envp_check_utils.c envp_change_utils.c free_utils.c str_array_utils.c mini_utils.c)

SRCS    = $(CFILES_SRCS) $(CFILES_INPUT) $(CFILES_CMD) $(CFILES_UTILS) $(CFILES_BLTIN)
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
