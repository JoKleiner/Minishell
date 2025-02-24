
NAME 		= libft.a
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror

PRINTF_DIR	= printf
GNL_DIR		= get_next_line
LIST_DIR	= ft_list
MEMO_DIR	= ft_memo
STR_DIR		= ft_str
CONV_DIR	= ft_convert
FURTH_DIR	= ft_further

OBJ_DIR		= obj
HEADER		= libft.h

SRCS_PRINTF = $(addprefix $(PRINTF_DIR)/, ft_printf.c ft_case_xx.c ft_case_p_u.c)
SRCS_GNL    = $(addprefix $(GNL_DIR)/, get_next_line.c get_next_line_utils.c)
SRCS_LIST   = $(addprefix $(LIST_DIR)/, ft_lstnew.c ft_lstlast.c ft_lstclear.c ft_lstadd_back.c)
SRCS_MEMO   = $(addprefix $(MEMO_DIR)/, ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_memfree.c)
SRCS_STR    = $(addprefix $(STR_DIR)/, ft_putstr_rev.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strndup.c)
SRCS_CONV   = $(addprefix $(CONV_DIR)/, ft_atoi.c ft_itoa.c)
SRCS_FURTH  = $(addprefix $(FURTH_DIR)/, ft_isalnum.c ft_isdigit.c ft_putendl.c ft_strchr.c ft_strmapi.c ft_strrchr.c \
			   ft_tolower.c ft_isalpha.c ft_isprint.c ft_putnbr.c ft_striteri.c ft_strncmp.c ft_strtrim.c ft_toupper.c \
			   ft_isascii.c ft_putchar.c ft_putstr.c ft_strlcat.c ft_strnstr.c ft_substr.c)

SRCS            = $(SRCS_PRINTF) $(SRCS_GNL) $(SRCS_LIST) $(SRCS_MEMO) $(SRCS_STR) $(SRCS_CONV) $(SRCS_FURTH) 
OBJS            = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))


all: $(NAME)


$(OBJ_DIR)/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@printf "Objects libft... \033[0;32mcreated\033[0m\n"
	@ar rcs $(NAME) $(OBJS)
	@printf "\033[0;32m$(NAME) successfully built!\033[0m\n"

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		printf "Remove $(NAME) o-files... "; \
		rm -rf $(OBJ_DIR); \
		printf "\033[0;31mRemoved.\033[0m\n"; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		printf "Remove $(NAME)... "; \
		rm -f $(NAME); \
		printf "\033[0;31mRemoved.\033[0m\n"; \
	fi

re: fclean all

.PHONY: all clean fclean re
